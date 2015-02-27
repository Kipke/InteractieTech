void number_oneActions(){
  // light is yellow
  lightColor(255,255,0); 
  // if door opens and no movement
  if(!doorClosed){
    doorWasOpen = true;
  }
  if(doorWasOpen && !motionDetected){
     shotsToFire = 1;
     // set state to triggered
     state = TRIGGERED;
     // start the degradation timer
     degradationTime = millis();
     doorWasOpen = false;
  }
  // ping the distance to see if the tp is used
  if(timeElapsed(prevPing, pingDelay)){
    pingDistance();
    prevPing = millis();
  }
  // if tp has been used
  if (!tpUsed && lastDistance < baselineDistance / 2) {
    tpUsed = true;
    Serial.println("tpUsed!");     
  }
  // if time > y and tpUsed
  if(tpUsed && timeElapsed(startTime, numberOneTime)){
     state = NUMBER_TWO; 
     tpUsed = false;
  }
}
