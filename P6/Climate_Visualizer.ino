#define blue_led 11
#define green_led 10
#define red_led 9
#define temp_resistor A1
#define photo_resistor A0

float light_value;
float temp_value;
float light_calc;
float temp_calc;
float voltage_temp;

char led;

String state = "";
String mode = "";

void setup() {
  pinMode(blue_led, OUTPUT); 
  pinMode(green_led, OUTPUT); 
  pinMode(red_led, OUTPUT);
  pinMode(temp_resistor, INPUT);
  pinMode(photo_resistor, INPUT);
  Serial.begin(9600);
  greeting();
}

void loop() {
  light_value = analogRead(photo_resistor);
  light_calc = (5. * light_value) / 1024.;
  temp_value = analogRead(temp_resistor);
  voltage_temp = (temp_value * 5.) / 1024.;
  temp_calc = (voltage_temp - 0.5) * 100.;
  digitalWrite(red_led, LOW);
  digitalWrite(blue_led, LOW);
  digitalWrite(green_led, LOW);
  if(light_value <= 1024. / 2.){
    state = "ON";
    mode = "Night";
    if(temp_calc <= 0)
    {
      digitalWrite(blue_led, HIGH);
      led = 'b';
    }
    else if (temp_calc > 0 && temp_calc <= 25)
    {
      digitalWrite(green_led, HIGH);
      led = 'g';
    }
    else
    {
      digitalWrite(red_led, HIGH);
      led = 'r';
    }
  }
  else{
    state = "OFF";
    mode = "Day"; 
    digitalWrite(red_led, LOW);
    digitalWrite(blue_led, LOW);
    digitalWrite(green_led, LOW); 
  }
  Debugging(state, mode);
  delay(5000);
}

void greeting(){
  Serial.println("****************************");
  Serial.println("********* Welcome **********");
  Serial.println("****************************");
  digitalWrite(blue_led, HIGH);
  digitalWrite(red_led, HIGH);
  digitalWrite(green_led, HIGH);
  delay(100);
  digitalWrite(blue_led, LOW);
  digitalWrite(red_led, LOW);
  digitalWrite(green_led, LOW);
  delay(200);
  digitalWrite(blue_led, HIGH);
  delay(100);
  digitalWrite(blue_led, LOW);
  digitalWrite(red_led, HIGH);
  delay(100);
  digitalWrite(red_led, LOW);
  digitalWrite(green_led, HIGH);
  delay(100);
  digitalWrite(green_led, LOW);
  delay(600);
}


void Debugging(String current_state, String mode){
  Serial.println("******* Light Value ********");
  Serial.print("Volt Value: ");
  Serial.println(light_calc);
  Serial.println("****************************");
  Serial.println("");
  Serial.println("***** Tempreture Value *****");
  Serial.print("Volts: ");
  Serial.println(voltage_temp);
  Serial.print("Temp: ");
  Serial.println(temp_calc);
  Serial.println("****************************");
  Serial.println("");
  Serial.println("******** Led Status ********");
  Serial.print("Current mode is ");
  Serial.println(mode);
  if(led == 'r')
  {
    Serial.print("Red Led is ");
    Serial.print(current_state);
    Serial.println(".");
  }
  else if (led == 'b')
  {
    Serial.print("Blue Led is ");
    Serial.print(current_state);
    Serial.println(".");
  }
  else
  {
    Serial.print("Green Led is ");
    Serial.print(current_state);
    Serial.println(".");
  }
  Serial.println("****************************");
  Serial.println("");
}
