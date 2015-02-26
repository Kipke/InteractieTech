void number_twoActions(){
    // light is red
    lightColor(255,0,0);
    // if door opens and no movement
    if(!doorClosed && !motionDetected){
       shotsToFire = 2; 
       // set state to triggered
       state = TRIGGERED;
       // start the degradation timer
       degradationTime = millis();
    } 
}
