const int distance = 7;

void setup() {
  Serial.begin(9600);
}

void loop()
{
  long duration, cm;
  pinMode(distance, OUTPUT);
  digitalWrite(distance, LOW);
  delayMicroseconds(5);
  digitalWrite(distance, HIGH);
  delayMicroseconds(10);
  digitalWrite(distance, LOW);

  pinMode(distance, INPUT);
  duration = pulseIn(distance, HIGH);
  cm = microsecondsToCentimeters(duration);
  
  Serial.println(cm);
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}
