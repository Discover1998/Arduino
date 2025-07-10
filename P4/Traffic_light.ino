int Red = 9;
int Yellow = 10;
int Green = 11;


void setup() {
  pinMode(Red, OUTPUT); 
  pinMode(Yellow, OUTPUT); 
  pinMode(Green, OUTPUT); 
}

void loop() {
  digitalWrite(Red, HIGH);
  delay(2000);
  digitalWrite(Red, LOW);
  digitalWrite(Yellow, HIGH);
  delay(1000);
  digitalWrite(Yellow, LOW);
  digitalWrite(Green,HIGH);
  delay(2000);
  digitalWrite(Green,LOW);
}
