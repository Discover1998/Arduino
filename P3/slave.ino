#include <Wire.h>
#define LED_PIN 12

byte ledState = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Wire.begin(1);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  Serial.begin(9600);
}

void loop() {
  delay(500);
}

void receiveEvent(int howMany) {
  while (Wire.available()) {
    ledState = Wire.read();
    Serial.print("Received: ");
    Serial.println(ledState);

    if (ledState == 1) {
      digitalWrite(LED_PIN, HIGH);
    } else {
      digitalWrite(LED_PIN, LOW);
    }
  }
}

void requestEvent() {
  Wire.write(ledState);
}
