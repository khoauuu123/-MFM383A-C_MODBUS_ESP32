#include <ModbusMaster.h>
ModbusMaster node;

#define RXD2 4
#define TXD2 27

void setup() {
  Serial.begin(115200);
  delay(200);

  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  node.begin(1, Serial2);
}

void loop() {
  uint8_t result;
  uint16_t data[10];
  result = node.readInputRegisters(0x0000, 10);
  if (result == node.ku8MBSuccess) {
    for (uint8_t j = 0; j < 10; j++) {
      data[j] = node.getResponseBuffer(j);
    }

    // In giá trị đọc được ra Serial Monitor
    Serial.print("Voltage V1N: ");
    Serial.println(convertFloat(data[0], data[1]));
    Serial.print("Voltage V2N: ");
    Serial.println(convertFloat(data[2], data[3]));
    Serial.print("Voltage V3N: ");
    Serial.println(convertFloat(data[4], data[5]));
    Serial.print("Average Voltage LN: ");
    Serial.println(convertFloat(data[6], data[7]));

  } else {
    Serial.print("Modbus Read Error: ");
    Serial.println(result);
  }
  delay(2000);
}

float convertFloat(uint16_t reg_low, uint16_t reg_high) {
  uint16_t data[2] = { reg_low, reg_high };
  float value;
  memcpy(&value, data, 4);
  return value;
}
