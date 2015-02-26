void cleaningActions(){
  // light is green
  lightColor(0,255,0);
  // if door closed or no movement
  //   state = STANDBY;
  // if door closes
  if(doorClosed || !motionDetected){  
     state = STANDBY;
  }
}
