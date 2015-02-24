void unknownActions(){
  // light is white
  lightColor(255,255,255);
    // turn screen backlight on
  digitalWrite(screenLED,LOW);
  // start timer -- timer already started in standby
  // if door closes
  // TODO Movement
  if(doorClosed){  
     state = NUMBER_ONE;
  }
  int t = millis() / 1000;
  // if enough time has elapsed before the door closes 
  // state = CLEANING;
  if(t - startTime > x){
     state = CLEANING; 
  }
  // if time > x
  //   state = CLEANING;
}
