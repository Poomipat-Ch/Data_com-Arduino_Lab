char myByte = 'A';

String outMessage = myByte + "This is Message form A";
char* cString = const_cast<char*>(outMessage.c_str());

void setup() {
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()){
    delay(1000);
    Serial.write(cString);
  }
}
