#include <SoftwareSerial.h>

SoftwareSerial kenta(10, 11);

void setup() {
  kenta.begin(57600);
  Serial.begin(115200);
}
void loop() {
  if(kenta.available()){
    Serial.write(kenta.read());
  }
}
