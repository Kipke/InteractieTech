void triggeredActions(){
  // light is flashing color of shots remaining
  // degradation timer and shots to fire magic :-)
  // if no movement
  if(shotsToFire == 0){
     state = STANDBY;
     return; 
  }
  //   start shot countdown
  if(shotTime == -1){
     shotTime = millis() / 1000;
  }
  int t = millis() / 1000;
  if (t - shotTime > shotDelay && shotTime != (-1)){    
    digitalWrite(13,HIGH);
    delay(500);
    digitalWrite(13,LOW);
    shotsToFire--;
    shotTime = -1;
  }
  // if shot countdown == 0
  //   fire shot;
  //   shotsToFire--;
  // if shotsToFire == 0
  //   state = STANDBY;
}
