int incomingByte = 0; // for incoming serial data

void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
}

void loop() {
  delay(500);
  Serial.println("Beep");
  // send data only when you receive data:
  while (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
  Serial.println(Serial.available());
    // say what you got:
//    Serial.print("I received: ");
//    Serial.println(incomingByte);
  }
}
