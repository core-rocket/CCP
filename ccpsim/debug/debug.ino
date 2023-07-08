#include <CCP_MCP2515.h>

#define CAN0_INT 2
#define CAN0_CS 3

CCP_MCP2515 CCP(CAN0_CS, CAN0_INT);

void setup() {
  Serial.begin(9600);  
  CCP.begin();
}

void loop() {
  delay(500);

  CCP.read_device();
  
  switch (CCP.id) {
    case 0:
      break;
    case CCP_A_accel_mss:
      Serial.print("ACC: ");
      Serial.println(CCP.data_fp16_2());
      break;
    case CCP_A_pressure_altitude_m:
      Serial.print("ALT: ");
      Serial.println(CCP.data_float());
      break;
    default:
      Serial.println(CCP.id);
      break;
  }
}
