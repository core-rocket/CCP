#! /usr/bin/env nix-shell
#! nix-shell -i python -p python310 python310Packages.fire python310Packages.pyserial

from dataclasses import dataclass
from typing import List
from serial import Serial
from fire import Fire
import asyncio
import csv
import enum
import struct


class SimType(enum.Enum):
    ACC = b'a'
    ALT = b'b'


@dataclass
class SimData:
    ty: SimType
    time: int
    value: float


def send_data(serial: Serial, data: SimData) -> None:
    serial.write(data.ty.value)
    serial.write(bytearray(struct.pack('<f', data.value)))


def simulate(serial, data: List[SimData]) -> None:
    loop = asyncio.get_event_loop()
    max_time = max([d.time for d in data]) + 1000
    loop.call_later(max_time/1000, loop.stop)
    for d in data:
        loop.call_later(d.time/1000, send_data, serial, d)
    try:
        loop.run_forever()
    finally:
        loop.close()


def parse(path: str, ty: SimType) -> List[SimData]:
    with open(path, 'r') as f:
        rdr = csv.reader(f)
        data = [
            SimData(ty, int(row[0]), float(row[1]))
            for row in rdr
        ]
    return data


def main(port: str, baudrate: int, acc: str, alt: str) -> None:
    with Serial(port, baudrate) as serial:
        data = parse(acc, SimType.ACC) + parse(alt, SimType.ALT)
        simulate(serial, data)


if __name__ == "__main__":
    Fire(main)
