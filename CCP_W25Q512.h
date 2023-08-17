#ifndef CCP_W25Q512_H
#define CCP_W25Q512_H

#include "Arduino.h"

#include <CCP.h>
#include <W25Q512.h>

#include "Queue.h"
// https://rb-station.com/blogs/article/arduino-queue

class CCP_W25Q512 : public CCP, public W25Q512
{
public:
    CCP_W25Q512(SPIClass &bus, uint8_t csPin, uint8_t CAN0_INT) : W25Q512(bus, csPin)
    {
        _csPin = csPin;
        _CAN0_INT = CAN0_INT;
    }
    int begin();
    void read_device();
    byte write_device(); // return sndStat
    void flash_buf();
    void clear_flash(bool flgwait);
    bool is_cleared();

    uint32_t flash_addr = 0x0000000;
    // 0x0100000;
    // 0x3FFFFFF;
    Queue<uint8_t> flashbuf = Queue<uint8_t>(1024);

    uint32_t flash_time = 0;

protected:
    uint8_t _csPin;
    uint8_t _CAN0_INT;

    const uint32_t SPI_W25Q512_CLOCK = 6000000;
};

#endif
