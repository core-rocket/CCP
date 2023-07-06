#include <SPI.h>
#include <string.h>
#include <CCP_MCP2515.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1331.h>

// #define NC0         0
// #define NC1         1
#define CAN0_INT 2
#define CAN0_CS 3
// #define SSD1331_cs  4
// #define SSD1331_dc  5
// #define SSD1331_rst 6

// Color definitions
// #define BLACK           0x0000
// #define BLUE            0x001F
// #define RED             0xF800
// #define GREEN           0x07E0
// #define CYAN            0x07FF
// #define MAGENTA         0xF81F
// #define YELLOW          0xFFE0
// #define WHITE           0xFFFF

// Adafruit_SSD1331 display = Adafruit_SSD1331(&SPI, SSD1331_cs, SSD1331_dc, SSD1331_rst);

// CAN
CCP_MCP2515 CCP(CAN0_CS, CAN0_INT);

// Other
char msgString[128];
char str_buf[7]; // 6+\0

void setup()
{
  delay(500);
  Serial.begin(2000000);
  //  pinMode(NC0, INPUT_PULLUP);
  //  pinMode(NC1, INPUT_PULLUP);
  pinMode(CAN0_CS, OUTPUT);
  //  pinMode(SSD1331_cs, OUTPUT);
  pinMode(CAN0_INT, INPUT);
  digitalWrite(CAN0_CS, HIGH);
  //  digitalWrite(SSD1331_cs, HIGH);

  // CAN
  CCP.begin();
  /*
    display.begin();
    display.setTextSize(1);
    display.fillScreen(BLACK);
    display.setTextColor(WHITE);

    display.setCursor(0, 0);
    display.println("main          V ");
    display.setCursor(0, 8);
    display.println("servo         V ");
    display.setCursor(0, 16);
    display.println("press        hPa");
    display.setCursor(0, 24);
    display.println("BMEalt        m ");
    display.setCursor(0, 32);
    display.println("GPSalt        m ");
    display.setCursor(0, 40);
    display.println("MPUacZ       mss");
    display.setCursor(0, 48);
    display.println("para            ");*/
}

void loop()
{
  if (!digitalRead(CAN0_INT)) // データ受信確認
  {
    CCP.read_device();
    if (CCP.id < 0x40)
    {
      CCP.string(str_buf, 7);
      sprintf(msgString, "ID,%03x,time,%d000,string,%s,,,,", CCP.id, CCP.time16(), str_buf);
    }
    else if (CCP.id < 0x80)
    {
      sprintf(msgString, "ID,%03x,time,%lu,uint32,%lu,,,,", CCP.id, CCP.time32(), CCP.data_uint32());
    }
    else if (CCP.id < 0xC0)
    {
      sprintf(msgString, "ID,%03x,time,%lu,float,%8.2f,,,,", CCP.id, CCP.time32(), CCP.data_float());
    }
    else
    {
      sprintf(msgString, "ID,%03x,time,%d000,fp16_0,%8.2f,fp16_1,%8.2f,fp16_2,%8.2f", CCP.id, CCP.time16(), CCP.data_fp16_0(), CCP.data_fp16_1(), CCP.data_fp16_2());
    }
    Serial.println(msgString);

    /*
        if (CCP.id == CCP_voltage_main) {
          unsigned long int time = micros();
          display.setCursor(36, 0);
          display.fillRect(36, 0, 42, 8, BLACK);
          display.println(CCP.data_float());
          Serial.println(micros() - time);
        }
        if (CCP.id == CCP_voltage_actuator) {
          unsigned long int time = micros();
          display.setCursor(36, 8);
          display.fillRect(36, 8, 42, 8, BLACK);
          display.println(CCP.data_float());
          Serial.println(micros() - time);
        }
        if (CCP.id == CCP_A_pressure_hPa) {
          unsigned long int time = micros();
          display.setCursor(36, 16);
          display.fillRect(36, 16, 42, 8, BLACK);
          display.println(CCP.data_float());
          Serial.println(micros() - time);
        }
        if (CCP.id == CCP_A_pressure_altitude_m) {
          unsigned long int time = micros();
          display.setCursor(36, 24);
          display.fillRect(36, 24, 42, 8, BLACK);
          display.println(CCP.data_float());
          Serial.println(micros() - time);
        }
        if (CCP.id == CCP_A_GNSS_altitude_mm) {
          unsigned long int time = micros();
          display.setCursor(36, 32);
          display.fillRect(36, 32, 42, 8, BLACK);
          display.println(CCP.data_uint32() / 1000);
          Serial.println(micros() - time);
        }
        if (CCP.id == CCP_A_accel_mss) {
          unsigned long int time = micros();
          display.setCursor(36, 40);
          display.fillRect(36, 40, 42, 8, BLACK);
          display.println(CCP.data_fp16_2());
          Serial.println(micros() - time);
        }
        if (CCP.id == CCP_parachute_judge) {
          unsigned long int time = micros();
          display.setCursor(36, 48);
          display.fillRect(36, 48, 42, 8, BLACK);
          CCP.string(str_buf, 7);
          display.println(str_buf);
          Serial.println(micros() - time);
        }
        if (CCP.id < 0x400) {
          unsigned long int time = micros();
          display.fillRect(0, 56, 96, 8, BLACK);
          display.setCursor(0, 56);
          display.println(CCP.id, HEX);
          display.setCursor(36, 56);
          CCP.string(str_buf, 7);
          display.println(str_buf);
          Serial.println(micros() - time);
        }*/
  }
}