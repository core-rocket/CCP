#include <CCP_MCP2515.h>

#define CAN0_INT        1
#define CAN0_CS         0
#define METHIONINE      "AUG"
#define AMBER           "UAG"
#define ERR_START_CODON "E01"
#define ERR_SIMTYPE     "E02"

CCP_MCP2515 CCP(CAN0_CS, CAN0_INT);
char buffer[8];
union { float f; uint32_t i; } f_bits;
uint8_t state = 0;
uint32_t length = 0;

void setup() {
  Serial.begin(9600);
  CCP.begin();
}

void check_amber() {
  switch (state) {
    case 0:
      buffer[0] = Serial.read();
      if (buffer[0] == AMBER[0]) state++;
      else state = 0;
    case 1:
      buffer[0] = Serial.read();
      if (buffer[0] == AMBER[0]) break;
      else if (buffer[0] == AMBER[1]) state++;
      else state = 0;
    case 2:
      buffer[0] = Serial.read();
      if (buffer[0] == AMBER[2]) state++;
      else state = 0;
    case 3:
      Serial.readBytes(buffer, 4);
      length = 0;
      for (int i = 0; i < 4; i++) {
        length |= (uint32_t)buffer[i] << i * 8;
      }
      state++;
  }
}

void send_data() {
  Serial.readBytes(buffer, 8);

  if (strncmp(buffer, METHIONINE, 3) != 0) {
    Serial.println(ERR_START_CODON);
  }

  f_bits = {0};
  for (int i = 4; i < 8; i++) {
    f_bits.i |= (uint32_t)buffer[i] << (i - 4) * 8;
  }

  switch (buffer[3]) {
    case 'a':
      CCP.fp16_to_device(CCP_A_accel_mss, 0, 0, f_bits.f);
      break;
    case 'b':
      CCP.float_to_device(CCP_A_pressure_altitude_m, f_bits.f);
      break;
    default:
      Serial.println(ERR_SIMTYPE);
      break;
  }

  length--;
  if (length <= 0) {
    state = 0;
    length = 0;
  }
}

void loop() {
  if (!Serial.available()) {
    return;
  }

  if (state < 4) {
    check_amber();
  } else {
    send_data();
  }
}
