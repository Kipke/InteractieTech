void number_oneActions(){
  // light is yellow
  lightColor(255,255,0); 
  // if door opens and no movement
  if(!doorClosed && !motionDetected){
     shotsToFire = 1;
     // set state to triggered
     state = TRIGGERED;
     // start the degradation timer
     degradationTime = millis();
  }

  // TODO: if toilet paper used
  //   tpUsed = true;
  if (millis() >= pingTimer) {   // pingSpeed milliseconds since last ping, do another ping.
    pingTimer += pingSpeed;      // Set the next ping time.
    sonar.ping_timer(echoCheck); // Send out the ping, calls "echoCheck" function every 24uS where you can check the ping status.
  }
  // if time > y and tpUsed
  //   state = NUMBER_TWO;
  if(timeElapsed(startTime, numberOneTime)){
     state = NUMBER_TWO; 
  }
}
