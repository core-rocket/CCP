#include <CCP_MCP2515.h>

#define CAN0_INT  1
#define CAN0_CS   0

CCP_MCP2515 CCP(CAN0_CS, CAN0_INT);
char buffer[5];
union { float f; int32_t i; } f_bits;

void setup() {
  Serial.begin(9600);
  CCP.begin();
}

void loop() {
  if (!Serial.available()) {
    return;
  }
  Serial.readBytes(buffer, 5);

  f_bits = {0};
  for (int i = 1; i < 5; i++) {
    f_bits.i |= (int32_t)buffer[i] << (i - 1) * 8;
  }

  switch (buffer[0]) {
    case 'a':
      CCP.fp16_to_device(CCP_A_accel_mss, 0, 0, f_bits.f);
      break;
    case 'b':
      CCP.float_to_device(CCP_A_pressure_altitude_m, f_bits.f);
      break;
  }
}
