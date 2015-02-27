const int distanceSensorTrigger = 11;
const int distanceSensorEcho = 3;
int distance;
long pingStart, pingStop;

void setup() {
  Serial.begin(9600);
  
  pinMode(distanceSensorEcho, INPUT);
  pinMode(distanceSensorTrigger, OUTPUT);
  attachInterrupt(1,measureDistance,CHANGE);
}

void loop()
{
  pingDistance();
  Serial.println(distance);  
}

void measureDistance(){  
  if(digitalRead(distanceSensorEcho)){
    pingStart = micros();  
  }
  else{
    pingStop = micros();
    long duration = pingStop - pingStart;
    distance = duration / 29 / 2;   

  }    
}

void pingDistance(){
  digitalWrite(distanceSensorTrigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(distanceSensorTrigger,LOW);  
}


