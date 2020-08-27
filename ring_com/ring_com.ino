#include<SoftwareSerial.h>

SoftwareSerial kenta(10,11);
char myByte;

void setup() {
  kenta.begin(57600);
  Serial.begin(9600);

  Serial.println("Enter ID:");  
  while (!(Serial.available() > 0)){
  }

  myByte = char(Serial.read());
  Serial.print("Your ID: ");
  Serial.println(myByte);
  delay(200);
}

void loop() {
  delay(100);
  if (kenta.available()){
    String buff = kenta.readString();
    if(myByte == buff[0]){
        Serial.print(buff[1]);
        for (int i = 2; i < buff.length(); i++){
            Serial.print(buff[i]);
        }
        Serial.println();
   }
   else{
     for(int i = 0; i < buff.length(); i++){
        kenta.write(buff[i]);
      }
    }
  }

  if(Serial.available()){
    String toSend="",buff="";
    
    while (Serial.available()){
       buff += char(Serial.read());
    }
    //Serial.println(buff);
    toSend += char(buff[0]);
    toSend += char(myByte);
    for(int i=1;i<buff.length();i++){
        toSend += char(buff[i]);
      }
    Serial.print("Me: ");
    for (int i = 2; i < buff.length(); i++){
     Serial.print(buff[i]); 
    }
    Serial.println();
     for(int i = 0; i < toSend.length(); i++){
        kenta.write(toSend[i]);
      }
    }
    
}
