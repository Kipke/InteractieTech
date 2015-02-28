// Reinier Maas     - 4131495
// Björn Molenmaker - 3843874

int pulses = 0;
int pulseElapsed = shotDelay / 10;
bool roomEmpty = false;
void triggeredActions(){
	// turn screen backlight on
	digitalWrite(screenLED, HIGH);
	// light is flashing color of shots remaining
	if(roomEmpty || doorClosed && !motionDetected){
                if(degradation && !roomEmpty && degradated == 0 && timeElapsed(startTime, degradationTime)){
                        degradated == 1; // Room was not empty in time so degredation
                        //Serial.println("degradation!");
                }
                else{
                        degradated == -1; // Room was empty in time no degredation
                        //Serial.println("no degradation!");
                }
                roomEmpty = true;
        }
        else{
                if(fireTriggered)
                        lightColor(0,255,0);
                else if(fireNumberTwo)
                        lightColor(255,0,0);
                else if(fireNumberOne)
                        lightColor(255,255,0);
                return;
        }
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
                //Serial.println("number two!");
                if(shotsToFireNumberTwo == 0 || degradated == 1){
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
                roomEmpty = false;
                degradated = 0;
        	return;
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
