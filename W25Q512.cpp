#include "Arduino.h"
#include "W25Q512.h"

/*
アドレスは4byteモードで動作させてる
書き込みは先頭アドレス(byte)単位を指定して、1~256個だけ連続して書き込める
読み込みは先頭アドレス(byte)単位を指定していくらでも連続して読み込める
消去はいろいろ単位あるけど実装したのはチップ全消去のみ(140秒ぐらいかかる)
256byte連続読み出しで0.8msぐらいかかる
8bit=1byte
256byte=1page
536870912bit
=67,108,864byte ←0-0x3FF,FFFF
=262,144page ←0-0x3FFFF

https://www.winbond.com/resource-files/W25Q512JV%20DTR%20RevD%2006292020%20133.pdf
https://nuneno.cocolog-nifty.com/blog/2014/03/arduinospiw25q6.html
https://github.com/Tamakichi/Arduino-W25Q64/blob/master/W25Q64/examples/sample/sample.ino
https://www.digikey.jp/ja/products/detail/winbond-electronics/W25Q512JVFIM/10244710
*/

W25Q512::W25Q512(SPIClass &bus, uint8_t csPin)
{
    _spi = &bus;
    _csPin = csPin;
}
int W25Q512::begin()
{
    pinMode(_csPin, OUTPUT);
    digitalWrite(_csPin, HIGH);
    _spi->begin();
    _spi->setDataMode(SPI_MODE0);
    delay(1);

    _spi->beginTransaction(SPISettings(SPI_W25Q512_CLOCK, MSBFIRST, SPI_MODE0)); 
    digitalWrite(_csPin, LOW);
    _spi->transfer(CMD_ENTER_4BYTE_ADDRESS_MODE);
    digitalWrite(_csPin, HIGH);                  
    _spi->endTransaction();              

    _spi->beginTransaction(SPISettings(SPI_W25Q512_CLOCK, MSBFIRST, SPI_MODE0)); 
    digitalWrite(_csPin, LOW);
    _spi->transfer(CMD_READ_STATUS_R3);
    uint8_t status_r3 = _spi->transfer(0x00);
    digitalWrite(_csPin, HIGH);
    _spi->endTransaction();

    if ((status_r3 & (0b00000001)))
    {
        return 4;
    }
    else
    {
        return 3;
    }
}

void W25Q512::readJEDEC_ID(byte *d)
{
    _spi->beginTransaction(SPISettings(SPI_W25Q512_CLOCK, MSBFIRST, SPI_MODE0)); 
    digitalWrite(_csPin, LOW);
    _spi->transfer(CMD_JEDEC_ID);
    for (byte i = 0; i < 3; i++)
    {
        d[i] = _spi->transfer(0x00);
    }
    digitalWrite(_csPin, HIGH);
    _spi->endTransaction();
}

// 書込み等の処理中チェック
// 戻り値: true:作業 、false:アイドル中
bool W25Q512::IsBusy()
{
    _spi->beginTransaction(SPISettings(SPI_W25Q512_CLOCK, MSBFIRST, SPI_MODE0)); 
    digitalWrite(_csPin, LOW);
    _spi->transfer(CMD_READ_STATUS_R1);
    uint8_t status_r1 = _spi->transfer(0x00);
    digitalWrite(_csPin, HIGH);
    _spi->endTransaction();

    if (status_r1 & SR1_BUSY_MASK)
        return true;
    return false;
}

void W25Q512::WriteEnable()
{
    _spi->beginTransaction(SPISettings(SPI_W25Q512_CLOCK, MSBFIRST, SPI_MODE0)); 
    digitalWrite(_csPin, LOW);
    _spi->transfer(CMD_WRIRE_ENABLE);
    digitalWrite(_csPin, HIGH);
    _spi->endTransaction();
}

void W25Q512::chipErase(bool flgwait)
{
    WriteEnable();
    _spi->beginTransaction(SPISettings(SPI_W25Q512_CLOCK, MSBFIRST, SPI_MODE0)); 
    digitalWrite(_csPin, LOW);
    _spi->transfer(CMD_CHIP_ERASE);
    digitalWrite(_csPin, HIGH);    
    _spi->endTransaction();
    while (IsBusy() & flgwait)
    {
        delay(1000);
        Serial.println("erasing");
    }
}

void W25Q512::write(uint32_t addr, byte *data, uint16_t n, bool flgwait) // n<=256
{
    WriteEnable();

    while (IsBusy())
        ;

    _spi->beginTransaction(SPISettings(SPI_W25Q512_CLOCK, MSBFIRST, SPI_MODE0)); 
    digitalWrite(_csPin, LOW);
    _spi->transfer(CMD_PAGE_PROGRAM);
    _spi->transfer((addr >> 24) & 0xff);
    _spi->transfer((addr >> 16) & 0xff);
    _spi->transfer((addr >> 8) & 0xff);
    _spi->transfer(addr & 0xff);
    for (uint16_t i = 0; i < n; i++)
    {
        _spi->transfer(data[i]);
    }
    digitalWrite(_csPin, HIGH);
    _spi->endTransaction();

    while (IsBusy() & flgwait)
        ;
}

void W25Q512::read(uint32_t addr, uint8_t *buf, uint32_t n)
{
    {
        _spi->beginTransaction(SPISettings(SPI_W25Q512_CLOCK, MSBFIRST, SPI_MODE0)); 
        digitalWrite(_csPin, LOW);
        _spi->transfer(CMD_READ_DATA);
        _spi->transfer((addr >> 24) & 0xff);
        _spi->transfer((addr >> 16) & 0xff);
        _spi->transfer((addr >> 8) & 0xff);
        _spi->transfer(addr & 0xff);
        for (uint32_t i = 0; i < n; i++)
        {
            buf[i] = _spi->transfer(0x00);
        }
        digitalWrite(_csPin, HIGH);
        _spi->endTransaction();
    }
}
