void cleaningActions(){
  // light is green
  lightColor(0,255,0);
  // if door closed or no movement
  //   state = STANDBY;  
  int v = analogRead(buttonPin);
  // if door closes
  if(v < 1000 && v > 700){  
     state = STANDBY;
  }
}
