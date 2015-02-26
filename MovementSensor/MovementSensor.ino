const int movement = 2;
String state = "";

void setup(void)
{
  Serial.begin(9600);
  pinMode(movement, INPUT);
  attachInterrupt(0,motionLow,CHANGE);

}

void loop(void) 
{
   // int moveState = digitalRead(movement);
    //Serial.println(moveState);
}
void motionLow(){
    int moveState = digitalRead(movement);
    if(moveState == 0){
      Serial.println("LOW");
    }
    else{
      Serial.println("HIGH");
    }
}
