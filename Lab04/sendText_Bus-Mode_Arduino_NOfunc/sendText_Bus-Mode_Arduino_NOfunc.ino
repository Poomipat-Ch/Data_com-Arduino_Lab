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
  while (!Serial.available());
  myID = char(Serial.read());
  Serial.print("My ID is : ");
  Serial.println(myID);
  Serial.print("\nReciver is : ");
  while (!Serial.available());
  reciver = char(Serial.read());
  Serial.println(reciver);
  

}


void flushRx() {
  while (kenta.available()) {
    uint8_t temp = kenta.read();
  }
}
void receiveData(String data){
  long current = millis();
    while(!kenta.available()){
      if (millis() - current >= 7000){
         Serial.println("Timeout");
         Serial.print("Retransmit Ack ");
         Serial.println(count_frame);
         String toSend = "`";
         toSend += data[2];
         toSend += data[1];
         toSend += count_frame;
         toSend += '`';
         for(int i = 0; i < toSend.length(); i++){
          kenta.write(toSend[i]);
          flushRx();
         }
         Serial.println();
         current = millis();
      }
    }
    String receiveText = kenta.readStringUntil('\n');
    Serial.println("Receive frame");
    Serial.print("Header      : ");
    Serial.println(receiveText.substring(1,3));
    Serial.print("Frame No.   : ");
    Serial.println(receiveText[3]);
    Serial.print("Data        : ");
    Serial.println(receiveText.substring(4,8));
    count_frame = receiveText[3] - '0';
    Serial.print("Checking  : ");
    Serial.println(receiveText[receiveText.length() - 1]);
    Serial.println("Received\n");
}

void receiveAck(String toSend){
    long current = millis();
    while(!kenta.available()){
      if (millis() - current >= 7000){
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
        Serial.println(toSend.substring(4,8));
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
}

void waitComing(){
    String data_in = "";
    if(kenta.available()){
    data_in = kenta.readStringUntil('\n');
    Serial.println("Receive frame");
    Serial.print("Header    : ");
    Serial.println(data_in.substring(1,3));
    Serial.print("Frame No. : ");
    Serial.println(data_in[3]);
    Serial.print("Data      : ");
    Serial.println(data_in.substring(4,8));
    Serial.print("Checking  : ");
    Serial.println(data_in[8]);
    
    if(checkACK(data_in)){
      count_frame = !count_frame;
      Serial.println("Received\n");
      Serial.print("Send Ack");
      Serial.println(count_frame);
      receiveAck(data_in);
      
    }else{
      Serial.println("Discarded\n");
    }
   }else{
      if(Serial.available()){
        Serial.print("\nSend Text : ");
        text_data = Serial.readStringUntil('\n');
        Serial.println(text_data);
        return;
      }
   }
    
}

bool checkACK(String data){
  int sum = 0;
  char check;
  for (int i = 1; i < data.length(); i++){
    for (int j = 0; j < 8; j++){
        if(bitRead(data[i],j) == 1){
          sum++;
        }
    }
  }
  if(sum % 2 == 0){
    check = '1';
  }else{
    check = '0';
  }
  if(data[8] == check){
    return true;
  }else{
    return false;
  }
  
}

void loop() {
  while(kenta.available()){
    String data_in = "";
    data_in = kenta.readStringUntil('\n');
    Serial.println("Receive frame");
    Serial.print("Header    : ");
    Serial.println(data_in.substring(1,3));
    Serial.print("Frame No. : ");
    Serial.println(data_in[3]);
    Serial.print("Data      : ");
    Serial.println(data_in.substring(4,8));
    Serial.print("Checking  : ");
    Serial.println(data_in[8]);
  }
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
    for (int i = 1; i < toSend.length(); i++) {
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

    receiveAck(toSend);

    text_data = text_data.substring(4);
}
