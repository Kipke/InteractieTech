void number_oneActions(){
  // light is yellow
  lightColor(255,255,0); 
  // if door opens or no movement
    if(!doorClosed){
       shotsToFire = 1;
       // set state to triggered
       state = TRIGGERED;
       // start the degradation timer
       degradationTime = millis();
    }

  // TODO: if toilet paper used
  //   tpUsed = true;
  // if time > y and tpUsed
  //   state = NUMBER_TWO;
  if(timeElapsed(startTime, numberOneTime)){
     state = NUMBER_TWO; 
  }
}
