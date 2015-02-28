// Reinier Maas     - 4131495
// Björn Molenmaker - 3843874

void number_oneActions(){
	// light is yellow
	lightColor(255,255,0); 
        // Set shots for this stage
        fireNumberOne = true;
        shotsToFireNumberOne = numberOneShots;
	// if door opens and no movement
	if(!doorClosed){
		doorWasOpen = true;
	}
	if(doorWasOpen && !motionDetected){
		// set state to triggered
		state = TRIGGERED;
		// start the degradation timer
		degradationTime = millis();
		doorWasOpen = false;
	}
	// ping the distance to see if the tp is used
	pingDistance();
	
	// if tp has been used
	if (!tpUsed && lastDuration < baselineDuration / 2) {
		tpUsed = true;
		Serial.println("tpUsed!");     
	}
	// if time > y and tpUsed
	if(tpUsed && timeElapsed(startTime, numberOneTime)){
		state = NUMBER_TWO;
		tpUsed = false;
	}
}
