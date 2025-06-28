#include <Wire.h>
#define Button 12
#define Sender_Led 13

void setup() {
  pinMode(Sender_Led, OUTPUT);
  pinMode(Button, INPUT_PULLUP);
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  bool state = digitalRead(Button);

  Wire.beginTransmission(1);
  Wire.write(state == LOW ? 1 : 0);
  Wire.endTransmission();

  digitalWrite(Sender_Led, state == LOW ? HIGH : LOW);
  Serial.println(state == LOW ? "Button pressed" : "Button released");

  Wire.requestFrom(1, 1);
  if (Wire.available()) {
    byte slave_state = Wire.read();
    if (slave_state == 1) {
      Serial.println("Secondary Uno is ON.");
    } else {
      Serial.println("Secondary Uno is OFF.");
    }
  }

  delay(200);
}
