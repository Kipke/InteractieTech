// Reinier Maas     - 4131495
// Björn Molenmaker - 3843874

int pulses = 0;
int pulseElapsed = shotDelay / 10;
void triggeredActions(){
	// turn screen backlight on
	digitalWrite(screenLED, HIGH);
	// light is flashing color of shots remaining
	if(timeElapsed(startTime,sprayTime) && doorClosed && !motionDetected){
                if(fireTriggered){
                        if(shotsToFireTriggered == 0){
		               fireTriggered = false;
	                }
                        else
                        {
                                // if triggered is pushed, the light should be green
                                lightColor(0,255,0);
                                flashing();
                                shotMaybe();
                        }
                }
                else if(fireNumberTwo){
                        if(shotsToFireNumberTwo == 0){
		               fireNumberTwo = false;
	                }
                        else
                        {
                                // if Number Two isn't finished, the light should be red
                                lightColor(255,0,0);
                                flashing();
                                shotMaybe();
                        }
                }
                else if(fireNumberOne){
                        if(shotsToFireNumberOne == 0){
		                fireNumberOne = false;
	                }
                        else
                        {
                                // if Number One isn't finished, the light should be yellow
                                lightColor(255,255,0);
                                flashing();
                                shotMaybe();
                        }
                }
                else{
                        // if no more shots left to fire, go to standby
                        state = STANDBY;
        		return;
                }
        }
        else
        {
                //Do something fun while waiting to spray
                //Cycle through colors of the comming shots
                cycle();
                return;
        }
        // Shots to fire magic
	
	
}
long cycleElapsed = 100;
int current = 0;
void cycle()
{
        if(timeElapsed(startTime,cycleElapsed))
        {
                switch(current){
                        case 0:
                                if(fireTriggered)
                                        lightColor(0,255,0);
                                break;
                        case 1:
                                if(fireNumberTwo)
                                        lightColor(255,0,0);
                                break;
                        case 2:
                                if(fireNumberOne)
                                        lightColor(255,255,0);
                                break;
                }
        }
        else{
                long timeRemaining = (startTime + cycleElapsed) - millis();
                lightIntensity(timeRemaining / cycleElapsed);
        }
}
void flashing()
{
        // start shot countdown if necessary
	if(shotTime == -1){
		shotTime = millis();
	}
	// flip the light
	if(timeElapsed(shotTime,pulseElapsed)){     
		flipLight(); 
		int pulseSpeed = shotDelay / (10 + 3 * pulses); 
		pulses++;     
		if(pulseSpeed < 50){
			pulseSpeed = 50;
		}
		pulseElapsed += pulseSpeed;
	}
}
void shotMaybe()
{
        // fire the shot if neccesary
	if (timeElapsed(shotTime,shotDelay) && shotTime != (-1)){
		// Reset the pulse settings for the next shot
                lightIntensity(1);
		shotTime = -1;
		pulses = 0;
		pulseElapsed = shotDelay / 10;
		digitalWrite(actuator,HIGH);
		delay(2000);
		digitalWrite(actuator,LOW);
		if(fireTriggered){
                        shotsToFireTriggered--;
                }
                else if(fireNumberTwo){
                        shotsToFireNumberTwo--;
                }
                else if(fireNumberOne){
                        shotsToFireNumberOne--;
                }
		// update the shotRemaining
		shotsRemaining--;
		// update the EEPROM
		// writeToEEPROM(shotsRemaining);
	}
}
