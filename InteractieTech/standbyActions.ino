// Reinier Maas     - 4131495
// Björn Molenmaker - 3843874

void standbyActions(){
  // light is off  
  lightColor(0,0,0);
  // turn screen backlight off
  digitalWrite(screenLED, LOW);
  // if motion or door
  // check if door is open and motion is detected
  if(!doorClosed && motionDetected){
       state = UNKNOWN;
       startTime = millis();
  }
}
