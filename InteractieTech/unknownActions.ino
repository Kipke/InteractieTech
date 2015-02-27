void unknownActions(){
  // light is white
  lightColor(255,255,255);
  // turn screen backlight on
  digitalWrite(screenLED, HIGH);
  // ping the distance to set a baseline for the distanceSensor
  if(timeElapsed(prevPing, pingDelay)){
    pingDistance();
    prevPing = millis();
  }
  // start timer -- timer already started in standby
  // if door closes  
  if(doorClosed){  
     state = NUMBER_ONE;
     startTime = millis();
  }
  // if enough time has elapsed before the door closes 
  // state = CLEANING;
  if(timeElapsed(startTime, cleaningTime)){
     state = CLEANING; 
  }
}
