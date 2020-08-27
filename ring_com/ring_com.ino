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
}

void loop() {
  if (kenta.available()){
    String buff = kenta.readString();
    if(myByte == buff[0]){
        Serial.println(buff);  
   }
   else{
      Serial.println("Not for you");
    }
  }

  if(Serial.available()){
    String toSend;
    toSend = ""+myByte;
    while (Serial.available()){
       toSend += char(Serial.read());
    }
    //Serial.println(toSend); debug
     for(int i = 0; i < toSend.length(); i++){
        kenta.write(toSend[i]);
      }
    }
    
}
