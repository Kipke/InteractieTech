const int distanceSensorTrigger = 3;
const int distanceSensorEcho = 11;
int distance = 0;
int timeout = 2500 // in microseconds
void setup() {
  Serial.begin(9600);
  
  pinMode(distanceSensorEcho, INPUT);
  pinMode(distanceSensorTrigger, OUTPUT);
  attachInterrupt(1,measureDistance,CHANGE);
}

void loop()
{
  digitalWrite(distanceSensorTrigger,HIGH);
  delay(10);
  digitalWrite(distanceSensorTrigger,LOW);  
  Serial.println(distance);  
}

void measureDistance(){
    if(digitalRead(distanceSensorTrigger)){
      int t = pulseIn(distanceSensorEcho, HIGH,timeout);      
      distance =  t / 29 / 2;       
    }
    
}


