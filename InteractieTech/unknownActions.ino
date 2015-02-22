void unknownActions(){
  // light is white
    // turn screen backlight on
  digitalWrite(screenLED,HIGH);
  // start timer -- timer already started in standby
  int v = analogRead(buttonPin);
  // if door closes
  if(v < 1000 && v > 700){  
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
