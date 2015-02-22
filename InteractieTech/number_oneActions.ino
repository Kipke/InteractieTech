void number_oneActions(){
  // light is yellow
  // if door opens or no movement
    int v = analogRead(buttonPin);
    if(v > 1000){
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
    int t = millis() / 1000;
  if(t - startTime > y){
     state = NUMBER_TWO; 
  }
}
