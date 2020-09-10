#include <SoftwareSerial.h>

SoftwareSerial kenta(10, 11);
char myID, reciver;
String text_data;
int count_frame = 0;

void setup() {
  Serial.begin(115200);
  kenta.begin(57600);
  delay(500);
  Serial.println("Enter ID : ");
  Serial.print("My ID is : ");
  while (!Serial.available());
  myID = char(Serial.read());
  Serial.println(myID);
  Serial.print("\nReciver is : ");
  while (!Serial.available());
  reciver = char(Serial.read());
  Serial.println(reciver);
  Serial.print("\nSend Text : ");
  while (!Serial.available());
  text_data = Serial.readStringUntil('\n');
  Serial.println(text_data);
}


void flushRx() {
  while (kenta.available()) {
    uint8_t temp = kenta.read();
  }
}

void loop() {
  if (text_data.length() > 0) {
    String toSend = "";
    String data = text_data.substring(0, 4);
    
    toSend += '`';
    toSend += reciver;
    toSend += myID;
    toSend += count_frame;
    if(data.length() < 4){
      for(int i = data.length(); i<4; i++){
        data += '~';
      }
    }
    toSend += data;

    int sum = 0;
    for (int i = 0; i < toSend.length(); i++) {
      for (int k = 0; k < 8; k++) {
        if (bitRead(toSend[i], k) == 1) {
          sum++;
        }
      }
    }
    
    if (sum % 2 == 0) {
      toSend += '1';
    } else {
      toSend += '0';
    }
    toSend += '`';
    
    Serial.print("Send frame : ");
    Serial.println(count_frame);
    Serial.print("Data       : ");
    Serial.println(data);
    Serial.println();

      long current = millis();
    while(!kenta.available()){
      if (millis() - current >= 3000){
         Serial.println("Timeout");
         Serial.print("Retransmit frame ");
         Serial.println(count_frame);
         Serial.print("Send frame : ");
         Serial.println(count_frame);
         Serial.print("Data       : ");
         for(int i = 0; i<toSend.length(); i++){
          kenta.write(toSend[i]);
          flushRx();
        }
        Serial.println(data);
        Serial.println();
        current = millis();
      }
    }
    String receiveText = kenta.readStringUntil('\n');
    Serial.println("Receive frame");
    Serial.print("Header    : ");
    Serial.println(receiveText.substring(1,3));
    Serial.print("ACK No.   : ");
    Serial.println(receiveText[3]);
    count_frame = receiveText[3] - '0';
    Serial.print("Checking  : ");
    Serial.println(receiveText[receiveText.length() - 1]);
    Serial.println("Received\n");

    text_data = text_data.substring(4);
    
  }else{
    Serial.print("\nSend Text : ");
    while (!Serial.available());
    text_data = Serial.readStringUntil('\n');
    Serial.println(text_data);
  }
}
