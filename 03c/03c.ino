#include <Wire.h>

void setup() {
  Serial.begin(115200);
  Wire.begin(48, 47);  // กำหนดขา SDA => GPIO48, SCL => GPIO47
  while (!Serial)
    ;
}


void loop() {
  Serial.println("Scanning...");
  for (uint8_t addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    uint8_t error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("Found an I2C device at address ");
      Serial.println(addr);
    }
  }
  delay(2000);  
}
