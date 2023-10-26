#include "CCP_W25Q512.h"

int CCP_W25Q512::begin()
{
    return W25Q512::begin();
}

void CCP_W25Q512::read_device()
{
    //Serial.println(flash_addr);
    byte rdata[14];
    W25Q512::read(flash_addr, rdata, 14);
    flash_addr += 14;
    if (flash_addr % 256 >= 252)
    {
        flash_addr += 256 - (flash_addr % 256);
    }
    flash_time = (((long unsigned int)rdata[0]) << 24) + (((long unsigned int)rdata[1]) << 16) + (((long unsigned int)rdata[2]) << 8) + ((long unsigned int)rdata[3]);
    id = (((long unsigned int)rdata[4]) << 8) + ((long unsigned int)rdata[5]);
    for (int i_msg = 0; i_msg < 8; i_msg++)
    {
        msg.msg_byte[i_msg] = rdata[i_msg + 6];
    }
}

byte CCP_W25Q512::write_device()
{
    flash_time = millis();
    flashbuf.push(((uint8_t)(flash_time >> 24) & 0xFF));
    flashbuf.push(((uint8_t)(flash_time >> 16) & 0xFF));
    flashbuf.push(((uint8_t)(flash_time >> 8) & 0xFF));
    flashbuf.push((uint8_t)(flash_time & 0xFF));

    flashbuf.push(((uint8_t)(id >> 8) & 0xFF));
    flashbuf.push((uint8_t)(id & 0xFF));
    
    for (uint8_t i = 0; i < 8; i++)
    {
        flashbuf.push(msg.msg_byte[i]);
    }
    return 0;
}

void CCP_W25Q512::flash_buf()
{
    // Serial.print("buflen");
    // Serial.println(flashbuf.count());
    if (flashbuf.count() > 0 && !W25Q512::IsBusy())
    {
        W25Q512::WriteEnable();

        SPI.beginTransaction(SPISettings(SPI_W25Q512_CLOCK, MSBFIRST, SPI_MODE0));
        digitalWrite(_csPin, LOW);
        SPI.transfer(CMD_PAGE_PROGRAM);
        SPI.transfer((flash_addr >> 24) & 0xff);
        SPI.transfer((flash_addr >> 16) & 0xff);
        SPI.transfer((flash_addr >> 8) & 0xff);
        SPI.transfer(flash_addr & 0xff);
        while (flashbuf.count() > 0 && digitalRead(_CAN0_INT))
        {
            for (uint8_t i_can_mes = 0; i_can_mes < 14; i_can_mes++)
            {
                SPI.transfer(flashbuf.pop());
                flash_addr++;
            }
            if (flash_addr % 256 >= 252)
            {
                flash_addr += 256 - (flash_addr % 256);
                break;
            }
        }
        digitalWrite(_csPin, HIGH);
        SPI.endTransaction();
    }
}

void CCP_W25Q512::clear_flash(bool flgwait)
{
    W25Q512::chipErase(flgwait);
    flashbuf.clear();
    flash_addr = 0x0000000;
}

bool CCP_W25Q512::is_cleared()
{
    uint32_t before_flash_addr = flash_addr;
    if (flash_addr != 0x0000000)
    {
        flash_addr = before_flash_addr;
        return false;
    }
    for (flash_addr = 0x0000000; flash_addr < 0x3F00000;flash_addr+= 0x10000){
        read_device();
        if (id != 0xffff)
        {
            flash_addr = before_flash_addr;
            return false;
        }
    }
    flash_addr = before_flash_addr;
    return true;
}