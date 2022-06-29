#ifndef W25Q512_H
#define W25Q512_H

#include "Arduino.h"
#include "SPI.h" // SPI library

#define CMD_WRIRE_ENABLE 0x06
#define CMD_WRITE_DISABLE 0x04

#define CMD_READ_STATUS_R1 0x05
#define CMD_READ_STATUS_R2 0x35
#define CMD_READ_STATUS_R3 0x15

#define CMD_PAGE_PROGRAM 0x12

#define CMD_CHIP_ERASE 0xC7

#define CMD_POWER_DOWN 0xB9

#define CMD_MANUFACURER_ID 0x90
#define CMD_READ_UNIQUE_ID 0x4B
#define CMD_JEDEC_ID 0x9f

#define CMD_READ_DATA 0x13

#define SR1_BUSY_MASK 0x01
#define SR1_WEN_MASK 0x02

#define CMD_ENTER_4BYTE_ADDRESS_MODE 0xB7
#define CMD_EXIT_4BYTE_ADDRESS_MODE 0xE9


class W25Q512
{
public:
    W25Q512(SPIClass &bus, uint8_t csPin);
    int begin();
    void write(uint32_t addr, byte *data, uint16_t n, bool flgwait);
    void read(uint32_t addr, byte *buf, uint32_t n);
    void WriteEnable();
    bool IsBusy();
    void chipErase(bool flgwait);
    void readJEDEC_ID(byte *d);

protected:
    SPIClass *_spi;
    uint8_t _csPin;
    const uint32_t SPI_W25Q512_CLOCK = 6000000;
};

#endif
