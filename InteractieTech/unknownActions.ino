// Reinier Maas     - 4131495
// Björn Molenmaker - 3843874

void unknownActions(){
	// light is white
	lightColor(255,255,255);
	// turn screen backlight on
	digitalWrite(screenLED, HIGH);
	// ping the distance to set a baseline for the distanceSensor
	pingDistance();
	// start timer -- timer already started in standby
	// if door closes  
	if(doorClosed && motionDetected){  
		state = NUMBER_ONE;
		startTime = millis();
	}
	if(doorClosed && !motionDetected){  
		state = STANDBY;
		startTime = millis();
	}
	// if enough time has elapsed before the door closes 
	// state = CLEANING;
	if(timeElapsed(startTime, cleaningTime)){
		state = CLEANING; 
	}
}
