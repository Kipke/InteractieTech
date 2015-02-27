// Reinier Maas     - 4131495
// Björn Molenmaker - 3843874

int pulses = 0;
int pulseElapsed = shotDelay / 10;;
void triggeredActions(){
	// light is flashing color of shots remaining
	// turn screen backlight on
	digitalWrite(screenLED, HIGH);
	// Shots to fire magic
	// if no more shots left to fire, go to standby
	if(shotsToFire == 0){
		state = STANDBY;
		return; 
	}
        // if there is only one shot left, the light should be yellow
	if(shotsToFire == 1){
		// light is yellow
		lightColor(255,255,0); 
	}
	//   start shot countdown if necessary
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
	// fire the shot if neccesary
	if (timeElapsed(shotTime,shotDelay) && shotTime != (-1)){    
		digitalWrite(actuator,HIGH);
		delay(2000);
		digitalWrite(actuator,LOW);
		shotsToFire--;
		// update the shotRemaining
		shotsRemaining--;
		// update the EEPROM
		// writeToEEPROM(shotsRemaining);
		// Reset the pulse settings for the next shot
		shotTime = -1;
		pulses = 1;
		pulseElapsed = shotDelay / 10;
		lightIntensity(1);
	}
}
