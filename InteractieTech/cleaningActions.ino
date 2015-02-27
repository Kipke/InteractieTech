// Reinier Maas     - 4131495
// Björn Molenmaker - 3843874

void cleaningActions(){
	// light is green
	lightColor(0,255,0);
	// if door closed or no movement	
	if(doorClosed || !motionDetected){  
                // then the state is standby
		state = STANDBY;
	}
}
