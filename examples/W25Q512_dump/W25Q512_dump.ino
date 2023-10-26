#include <SPI.h>
#include <TimerTCC0.h>
#include <CCP_MCP2515.h>
#include <CCP_W25Q512.h>
#include <string.h>

#define CAN0_CS       0
#define CAN0_INT      1
#define FLASH_CS      2
#define LED_YELLOW  LED_BUILTIN
#define LED_BLUE    PIN_LED_RXL

//FLASH
CCP_W25Q512 CCP_flash(SPI, FLASH_CS, CAN0_INT);

//Other
char msgString[128];
char str_buf[7]; // 6+\0


void setup() {
  delay(500);
  pinMode(CAN0_CS   , OUTPUT);
  pinMode(CAN0_INT   , INPUT);
  pinMode(FLASH_CS  , OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  digitalWrite(CAN0_CS    , HIGH);
  digitalWrite(FLASH_CS   , HIGH);
  digitalWrite(LED_YELLOW    , HIGH);
  digitalWrite(LED_BLUE    , HIGH);

  Serial.begin(2000000);

  //FLASH
  CCP_flash.begin();

  TimerTcc0.initialize(100000);//100,000us=10Hz
  TimerTcc0.attachInterrupt(timerIsr);

  while (!Serial) {

  }

    // if the file is available, write to it:
    while (CCP_flash.flash_addr < 0x3FFFF00 && CCP_flash.id != 0xffff) {
      //delay(1);
      for (int i = 0; i < 18; i++) { //18=256/14
        CCP_flash.read_device();
        if (CCP_flash.id < 0x40)
        {
          CCP_flash.string(str_buf, 7);
          sprintf(msgString, "flash_time,%lu,ID,%03x,time,%d000,string,%s,,,,", CCP_flash.flash_time, CCP_flash.id , CCP_flash.time16(), str_buf);
        }
        else if (CCP_flash.id < 0x80)
        {
          sprintf(msgString, "flash_time,%lu,ID,%03x,time,%lu,uint32,%lu,,,,", CCP_flash.flash_time, CCP_flash.id , CCP_flash.time32(), CCP_flash.data_uint32());
        }
        else if (CCP_flash.id < 0xC0)
        {
          sprintf(msgString, "flash_time,%lu,ID,%03x,time,%lu,float,%8.2f,,,,", CCP_flash.flash_time, CCP_flash.id , CCP_flash.time32(), CCP_flash.data_float());
        }
        else
        {
          sprintf(msgString, "flash_time,%lu,ID,%03x,time,%d000,fp16_0,%8.2f,fp16_1,%8.2f,fp16_2,%8.2f", CCP_flash.flash_time, CCP_flash.id, CCP_flash.time16(), CCP_flash.data_fp16_0(), CCP_flash.data_fp16_1(), CCP_flash.data_fp16_2());
        }
        Serial.println(msgString);
      }
    }
    while (true) {
      Serial.println("complete");
      delay(500);
    }
}

void loop() {
}

void timerIsr()
{
  digitalWrite(LED_BLUE    , !digitalRead(LED_BLUE));
}
