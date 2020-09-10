byte state;
void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  if (Serial.available() > 0) {
    state = Serial.read();
    state = state - '0';
    if (state == 1) {
      digitalWrite(13, HIGH);
    }else{
      digitalWrite(13, LOW);
    }
  }
  delay(50);
}
