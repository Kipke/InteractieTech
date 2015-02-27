// Reinier Maas     - 4131495
// Björn Molenmaker - 3843874

void number_twoActions(){
	// light is red
	lightColor(255,0,0);
        // Set shots for this stage
        fireNumberOne = true;
        shotsToFireNumberTwo = numberTwoShots;
        
	if(!doorClosed){
		doorWasOpen = true;
	}
	// if door opens and no movement
	if(doorWasOpen && !motionDetected){ 
		// set state to triggered
		state = TRIGGERED;
		// start the degradation timer
		degradationTime = millis();
		doorWasOpen = false;
	} 
}
