#include <SoftwareSerial.h>

SoftwareSerial gps2ard = SoftwareSerial(2, 3);
// rx 2, tx 3
void setup() {
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  gps2ard.begin(9600);
  Serial.begin(9600);

}

void loop() {
  gps2ard.listen();
  while (gps2ard.available() >0){
    char inByte = gps2ard.read();
    Serial.write(inByte);
    // IMPORTANT NOTE: Arduino HW serial writes to D1 (TX) and is **5V** logic. 
  }

}
