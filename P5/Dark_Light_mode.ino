#define yellow 11
#define red 9
#define photo_resistor A0

void setup() {
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(photo_resistor, INPUT);
  Serial.begin(9600);
}

void loop() {
  float light_value = 0.0;
  
  for (int i = 0; i < 10; i++) {
    light_value += analogRead(photo_resistor);
    delay(5);
  }
  light_value = light_value / 10.0;

  Serial.print("Current photoresistor value: ");
  Serial.println(light_value);

  if (light_value >= 1023.0 / 2.0) {
    digitalWrite(yellow, HIGH);
    digitalWrite(red, LOW);
    Serial.println("The Yellow light ON.");
    delay(5000);
    digitalWrite(yellow, LOW);
    Serial.println("The Yellow light OFF.");
  } else {
    digitalWrite(red, HIGH);
    digitalWrite(yellow, LOW);
    Serial.println("The Red light ON.");
    delay(5000);
    digitalWrite(red, LOW);
    Serial.println("The Red light OFF.");
  }
  Serial.println("");
  delay(100);
}
