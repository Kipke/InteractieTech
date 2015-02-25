void unknownActions(){
  // light is white
  lightColor(255,255,255);
  // turn screen backlight on
  digitalWrite(screenLED, HIGH);
  // start timer -- timer already started in standby
  // if door closes
  // TODO Movement
  if(doorClosed){  
     state = NUMBER_ONE;
     startTime = millis();
  }
  // if enough time has elapsed before the door closes 
  // state = CLEANING;
  if(timeElapsed(startTime, cleaningTime)){
     state = CLEANING; 
  }
  // if time > x
  //   state = CLEANING;
}
