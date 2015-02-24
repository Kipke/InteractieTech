void standbyActions(){
  // light is off  
  lightColor(0,0,0);
  // turn screen backlight off
  digitalWrite(screenLED,HIGH);
  // if motion or door
  // check if door is open 
  // TODO: MOTION
  if(!doorClosed){
       state = UNKNOWN;
       startTime = millis() / 1000;
  }
}
