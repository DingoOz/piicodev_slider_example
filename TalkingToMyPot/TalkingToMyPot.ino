// Basic example of reading the Core Electronics PiicoDev Slider Potentiometer
// See piico.dev/p22
//
// Based on simple I2C master and slave demo - Earle F. Philhower, III
// 
// Apache License 2.0
// Dec 2023

#include <Wire.h>

void setup() {
  Serial.begin(115200);
   while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
  
  Wire.setSDA(8);
  Wire.setSCL(9);
  Wire.begin();
  
  Serial.println("Starting Pot reading routine...");

}

void loop() {
  uint16_t recBuffer;   //Place to store the values received

  //Sending command to request data from piicoDev pot
  Wire.beginTransmission(0x35);   //Default value of the piicodev slider
  Wire.write(0x05);   //Core piicodev Slider uses register 0x05 to read the pot value. See Core github firmware for slider pot.
  Wire.endTransmission();

  // Read from the slave and print out
  Wire.requestFrom(0x35, 2);  //Pot value is provided as a uint16 so it needs 2 bytes
  while (Wire.available()) {
    Wire.readBytes((uint8_t*)&recBuffer, 2);  //Store the 2 bytes received in the uint16_t buffer directly. Values range from 0 to 1023.
    Serial.printf("Slider_value : %04u\r\n", __builtin_bswap16(recBuffer));  //print as an integer, padded up to 4 zeros
  }
  delay(500);
}
