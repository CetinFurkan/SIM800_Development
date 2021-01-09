#include <SoftwareSerial.h>

SoftwareSerial mySerial(7, 8);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  delay(200);
  while (Serial.available()) {
    mySerial.write(Serial.read());
  }
  delay(200);
}
