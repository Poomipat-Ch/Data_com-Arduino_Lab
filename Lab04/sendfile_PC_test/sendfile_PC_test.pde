import processing.serial.*;
import cc.arduino.*;


Arduino arduino;
int ledPin = 13;

void setup()
{
  println(Arduino.list());
  arduino = new Arduino(this,"COM9", 57600);
  arduino.pinMode(ledPin, Arduino.OUTPUT);
}

void draw()
{
  
  arduino.digitalWrite(ledPin, Arduino.HIGH);
  delay(500);
  arduino.digitalWrite(ledPin, Arduino.LOW);
  delay(1000);
}
