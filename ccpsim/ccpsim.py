#! /usr/bin/env nix-shell
#! nix-shell -i python -p python311 python311Packages.click python311Packages.pyserial-asyncio

from asyncio import AbstractEventLoop, Protocol, BaseTransport, get_event_loop
from dataclasses import dataclass
from serial_asyncio import create_serial_connection
from typing import Self, List, Optional, Callable
import click
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

    def parse(path: str, ty: SimType) -> List[Self]:
        with open(path, 'r') as f:
            rdr = csv.reader(f)
            data = [SimData(ty, int(row[0]), float(row[1])) for row in rdr]
        return data


class SimErrorType(enum.Enum):
    StartCodon = b'E01'


class SimError(Exception):
    ty: SimErrorType

    def __init__(self, ty: SimErrorType):
        self.ty = ty
        super().__init__(f"SimError: {ty.value}")


class SimProtocol(Protocol):
    MAGIC_METHIONINE = b'AUG'

    loop: AbstractEventLoop
    transport: Optional[BaseTransport]
    data: List[SimData]

    def __init__(self, data: List[SimData]) -> None:
        super().__init__()
        self.loop = get_event_loop()
        self.data = data

    def connection_made(self, transport: BaseTransport) -> None:
        self.transport = transport
        self.__simulate()

    def connection_lost(self, exc: Exception | None) -> None:
        pass

    # def pause_writing(self) -> None:
    # def resume_writing(self) -> None:

    def data_received(self, data: bytes) -> None:
        if data.strip() == SimErrorType.StartCodon.value:
            raise SimError(SimErrorType.StartCodon)

    # def eof_received(self) -> bool | None:

    def __send_data(self, data: SimData) -> None:
        if self.transport is not None:
            self.transport.write(self.MAGIC_METHIONINE)
            self.transport.write(data.ty.value)
            self.transport.write(bytearray(struct.pack('<f', data.value)))

    def __simulate(self) -> None:
        max_time = max([d.time for d in self.data]) + 1000
        self.loop.call_later(max_time/1000, self.loop.stop)
        for data in self.data:
            self.loop.call_later(data.time/1000, self.__send_data, data)

    @staticmethod
    def create(acc: str, alt: str) -> Callable[[], Self]:
        data = SimData.parse(acc, SimType.ACC) + SimData.parse(alt, SimType.ALT)
        return lambda: SimProtocol(data)


@click.command()
@click.option("--port", type=str, required=True)
@click.option("--baudrate", type=int, required=True)
@click.option("--acc", type=click.Path(exists=True), required=True)
@click.option("--alt", type=click.Path(exists=True), required=True)
def main(port: str, baudrate: int, acc: str, alt: str) -> None:
    loop = get_event_loop()
    coroutine = create_serial_connection(loop, SimProtocol.create(acc, alt), port, baudrate)
    loop.run_until_complete(coroutine)
    try:
        loop.run_forever()
    finally:
        loop.close()


if __name__ == '__main__':
    main()
