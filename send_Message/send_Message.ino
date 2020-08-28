#include <SoftwareSerial.h>

SoftwareSerial kenta(10,11);
String myByte;

void setup() {
  Serial.begin(9600);

  kenta.begin(57600);
  delay(100);
  Serial.println("Enter ID : ");
  while (!(Serial.available())){
  }
  myByte = Serial.readStringUntil('\n');
  Serial.print("Your ID : ");
  Serial.println(myByte);
  delay(200);
  

}

void loop() {
  if (Serial.available()){
    String tosend = ""+myByte;
    tosend += Serial.readStringUntil('\n');
    Serial.print("Me: ");
    for (int i = 3; i < tosend.length(); i++){
      Serial.print(tosend[i]);
    }
    Serial.println();
    for (int i = 0; i < tosend.length(); i++){
      kenta.write(tosend[i]);
    }
  } 

  if (kenta.available()){
    String recive = "";
    recive = kenta.readStringUntil('\n');
    if (recive[1] == myByte[0]){
      Serial.print(recive[0]);
      for(int i = 2; i < recive.length(); i++){
        Serial.print(recive[i]);
      }
      Serial.println();
      
    }
    else{
       for(int i = 0; i < recive.length(); i++){
        kenta.print(recive[i]);
      }
    }
  }

}
