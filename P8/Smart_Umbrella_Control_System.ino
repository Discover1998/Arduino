#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define red_rgb 7
#define green_rgb 5
#define blue_rgb 6

#define photosens A0
#define right_servo A2
#define left_servo A1
#define tempsens A3

#define CLOSED_LEFT 90
#define CLOSED_RIGHT 90
#define OPEN_LEFT 30
#define OPEN_RIGHT 150

LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo rightServo;
Servo leftServo;

float temperature = 0.0;
float volt_temp = 0.0;
float light = 0.0;

const char system_ready[] = "System is ready!";

void setup() {
  Serial.begin(9600);

  pinMode(red_rgb, OUTPUT);
  pinMode(green_rgb, OUTPUT);
  pinMode(blue_rgb, OUTPUT);

  pinMode(photosens, INPUT);
  pinMode(tempsens, INPUT);

  leftServo.attach(left_servo);
  rightServo.attach(right_servo);

  leftServo.write(CLOSED_LEFT);
  rightServo.write(CLOSED_RIGHT);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print(system_ready);
  delay(1000);
  lcd.clear();

  digitalWrite(red_rgb, HIGH);
  delay(300);
  digitalWrite(red_rgb, LOW);

  digitalWrite(green_rgb, HIGH);
  delay(300);
  digitalWrite(green_rgb, LOW);

  digitalWrite(blue_rgb, HIGH);
  delay(300);
  digitalWrite(blue_rgb, LOW);
}

void loop() {
  volt_temp = 0;

  for (int i = 0; i < 10; i++) {
    volt_temp += analogRead(tempsens);
    delay(10);
  }

  volt_temp = volt_temp / 10.0;
  volt_temp = (volt_temp * 5.0) / 1024.0;
  temperature = (volt_temp - 0.5) * 100.0;

  light = analogRead(photosens);

  Serial.print("Light: ");
  Serial.println(light);

  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.println(" C");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature, 1);
  lcd.print(" C");

  lcd.setCursor(0, 1);

  if (light >= 512) {
    Serial.println("Light Mode!");

    digitalWrite(red_rgb, LOW);
    digitalWrite(green_rgb, LOW);
    digitalWrite(blue_rgb, LOW);

    if (temperature >= 25) {
      lcd.print("Hot Day!");
      leftServo.write(OPEN_LEFT);
      rightServo.write(OPEN_RIGHT);
    } 
    else if (temperature >= 20) {
      lcd.print("Nice Day!");
      leftServo.write(OPEN_LEFT);
      rightServo.write(OPEN_RIGHT);
    } 
    else {
      lcd.print("Too Cold!");
      leftServo.write(CLOSED_LEFT);
      rightServo.write(CLOSED_RIGHT);
    }
  } 
  else {
    Serial.println("Dark Mode!");

    leftServo.write(CLOSED_LEFT);
    rightServo.write(CLOSED_RIGHT);

    if (temperature >= 25) {
      lcd.print("Hot Night!");
      digitalWrite(red_rgb, HIGH);
      digitalWrite(green_rgb, LOW);
      digitalWrite(blue_rgb, LOW);
    } 
    else if (temperature >= 20) {
      lcd.print("Nice Night!");
      digitalWrite(red_rgb, LOW);
      digitalWrite(green_rgb, HIGH);
      digitalWrite(blue_rgb, LOW);
    } 
    else {
      lcd.print("Too Cold!");
      digitalWrite(red_rgb, LOW);
      digitalWrite(green_rgb, LOW);
      digitalWrite(blue_rgb, HIGH);
    }
  }

  delay(1000);
}
