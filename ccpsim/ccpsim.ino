#include <CCP_MCP2515.h>

#define CAN0_INT        1
#define CAN0_CS         0
#define METHIONINE      "AUG"
#define ERR_START_CODON "ERR_START_CODON"

CCP_MCP2515 CCP(CAN0_CS, CAN0_INT);
char buffer[8];
union { float f; int32_t i; } f_bits;

void setup() {
  Serial.begin(9600);
  CCP.begin();
}

void loop() {
  if (!Serial.available()) {
    return;
  }
  Serial.readBytes(buffer, 8);

  if (strncmp(buffer, METHIONINE, 3) != 0) {
    Serial.println(ERR_START_CODON);
  }

  f_bits = {0};
  for (int i = 4; i < 8; i++) {
    f_bits.i |= (int32_t)buffer[i] << (i - 4) * 8;
  }

  switch (buffer[3]) {
    case 'a':
      CCP.fp16_to_device(CCP_A_accel_mss, 0, 0, f_bits.f);
      break;
    case 'b':
      CCP.float_to_device(CCP_A_pressure_altitude_m, f_bits.f);
      break;
  }
}
