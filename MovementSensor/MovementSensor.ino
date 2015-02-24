const int movement = 8;

void setup(void)
{
  Serial.begin(9600);
  pinMode(movement, INPUT);
}

void loop(void) 
{
  int moveState = digitalRead(movement);
  Serial.println(moveState);
}
