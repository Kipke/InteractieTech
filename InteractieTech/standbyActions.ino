void standbyActions(){
  // light is off  
  lightColor(0,0,0);
  // turn screen backlight off
  digitalWrite(screenLED,LOW);
  // if motion or door
  // check if door is open 
  // TODO: MOTION
  int v = analogRead(buttonPin);
  if(v > 1000){
       state = UNKNOWN;
       startTime = millis() / 1000;
  }
}
