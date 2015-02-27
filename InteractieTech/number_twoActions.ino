void number_twoActions(){
    // light is red
    lightColor(255,0,0);
    if(!doorClosed){
      doorWasOpen = true;
    }
    // if door opens and no movement
    if(doorWasOpen && !motionDetected){
       shotsToFire = 2; 
       // set state to triggered
       state = TRIGGERED;
       // start the degradation timer
       degradationTime = millis();
       doorWasOpen = false;
    } 
}
