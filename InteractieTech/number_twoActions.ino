void number_twoActions(){
  // light is red
  lightColor(255,0,0);
  // if door opens or no movement
    // if door opens or no movement
    int v = analogRead(buttonPin);
    if(!doorClosed){
       shotsToFire = 2; 
       // set state to triggered
       state = TRIGGERED;
       // start the degradation timer
       degradationTime = millis();
    } 
}
