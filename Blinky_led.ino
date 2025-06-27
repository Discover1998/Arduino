#define led 2

void setup()
{
  pinMode(led, OUTPUT);
}


void loop()
{
  while(1){
    digitalWrite(led, 1);
    delay(3000);
    digitalWrite(led, 0);
    delay(3000);
  }

}