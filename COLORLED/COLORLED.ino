const int pinRed = 4;
const int pinBlue = 9;
const int pinGreen = 10;

void setup(void)
{
  Serial.begin(9600);
  pinMode(pinRed, OUTPUT);
  pinMode(pinBlue, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  digitalWrite(pinGreen, LOW);
  digitalWrite(pinRed, LOW);
  digitalWrite(pinBlue, LOW);
}

void loop(void) 
{
   Serial.println("Red");
   digitalWrite(pinGreen, LOW);
   digitalWrite(pinRed, HIGH);
   delay(10000);
   Serial.println("Blue");
   digitalWrite(pinRed, LOW);
   digitalWrite(pinBlue, HIGH);
   delay(10000);
   Serial.println("Green");
   digitalWrite(pinBlue, LOW);
   digitalWrite(pinGreen, HIGH);
   delay(10000);
}
