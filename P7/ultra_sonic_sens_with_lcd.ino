#include <Wire.h>
#include <LiquidCrystal_I2C.h>


const int GreenLed = 5;
const int RedLed = 3;
const int BlueLed = 4;
const int trigPin = A3;
const int echoPin = A2;
const int buzzerPin = 6;
LiquidCrystal_I2C lcd(0x27, 16, 2);

long duration;
float distanceCm;

void setup() {
  Serial.begin(9600);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(GreenLed, OUTPUT);
  pinMode(RedLed, OUTPUT);
  pinMode(BlueLed, OUTPUT);
  
  pinMode(buzzerPin, OUTPUT);
  
  digitalWrite(GreenLed, HIGH);
  digitalWrite(RedLed, HIGH);
  
  delay(100);
  
  digitalWrite(GreenLed, LOW);
  digitalWrite(RedLed, LOW);
  
  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0,0);
  lcd.print("System Booting...");
  lcd.clear();

}

void loop() {
  digitalWrite(trigPin, LOW);
  
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  
  delayMicroseconds(10);
  
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate distance: (Time * Speed of Sound) / 2 (there and back)
  // Speed of sound is: 0.0343 cm per microsecond
  distanceCm = (duration * 0.0343) / 2;
  
  if (distanceCm >= 160.0){
    digitalWrite(GreenLed, HIGH);
    digitalWrite(RedLed, LOW);
    digitalWrite(BlueLed,LOW);
    lcd.print("Dist: ");
    lcd.print(distanceCm, 1);
    lcd.print(" cm      ");
    lcd.setCursor(0, 1);
    lcd.print("It's safe!");
  }
  else if (distanceCm >= 60.0 && distanceCm < 160.0){
    digitalWrite(BlueLed, HIGH);
    digitalWrite(GreenLed, LOW);
    digitalWrite(RedLed, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Dist: ");
    lcd.print(distanceCm, 1);
    lcd.print(" cm      ");
    lcd.setCursor(0, 1);
    for (int i = 0; i < 2; i++) {
      tone(buzzerPin, 251, 1000);
      delay(200);
      noTone(buzzerPin);
      delay(200);
    }
  }
  else{
    digitalWrite(RedLed, HIGH);
    digitalWrite(GreenLed, LOW);
    digitalWrite(BlueLed,LOW);
    lcd.print("Dist: ");
    lcd.print(distanceCm, 1);
    lcd.print(" cm      ");
    lcd.setCursor(0, 1);
    lcd.print("It's unsafe!");
    for (int i = 0; i < 5; i++) {
      tone(buzzerPin, 500, 1000);
      delay(50);
      noTone(buzzerPin);
      delay(50);
    }
  }
  
  Serial.print("Distance: ");
  Serial.print(distanceCm);
  Serial.println(" cm");
  
  delay(500);
  lcd.clear();
}
