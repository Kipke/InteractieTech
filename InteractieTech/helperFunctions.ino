// Reinier Maas     - 4131495
// Björn Molenmaker - 3843874

String currentText[2];

void print(int line, const String& text){  
	// if new text has to be written
	if(currentText[line] != text){
		// clear the display and set the cursor at 0,0 
		lcd.clear();
		lcd.setCursor(0,0);
		// set the new text as the currentText
		currentText[line] = text;
		// print the first line
		for(int j = 0; j< 2;j++){
			// set the cursor at the correct position
			lcd.setCursor(0,j);  
			for(int i = 0; i< currentText[j].length();i++){
				// if there is a special character, deal with it
				if(currentText[j][i] == '%'){
					if(isDigit(currentText[j][i+1])){
						char c = currentText[j][i+1] - '0';
						//int t = c.toInt();
						lcd.write(byte(c));
						i+=2;
					}
				}
				// otherwise just print the character
				lcd.print(currentText[j][i]);      
			}
		}
	}
}
void printMenu(const String& text, unsigned long divide){
        print(0, text);
	if (menuSelect){
		print(1, change + String(menuValue / divide));
	}
	else{
		print(1, String(menuValue / divide));
	}
}

int curRed, curGreen, curBlue;
float curIntensity = 1;
float dimIntensity = 1;
void lightColor(int red, int green, int blue){
	// set the new values
	curRed   = red;
	curGreen = green;
	curBlue  = blue;
	// update the light
	analogWrite(redPin,  255 - curRed * dimIntensity * curIntensity);
	analogWrite(greenPin,255 - curGreen * dimIntensity * curIntensity);
	analogWrite(bluePin, 255 - curBlue * dimIntensity * curIntensity);
}

void lightIntensity(float intensity){
	// set the new value
	curIntensity = intensity;
	// update the lights
	analogWrite(redPin,  255 - curRed * dimIntensity * curIntensity);
	analogWrite(greenPin,255 - curGreen * dimIntensity * curIntensity);
	analogWrite(bluePin, 255 - curBlue * dimIntensity * curIntensity);
}
void flipLight(){
	//set the new intensity
	curIntensity = 1 - curIntensity; 
	// update the lights
	analogWrite(redPin,  255 - curRed * dimIntensity * curIntensity);
	analogWrite(greenPin,255 - curGreen * dimIntensity * curIntensity);
	analogWrite(bluePin, 255 - curBlue * dimIntensity * curIntensity);  
}
void dimLight(){
        //set the new dimming
        float light = (float)analogRead(lightPin);
	dimIntensity = 1.0 - ((light / 1024.0) * 4.0); 
        dimIntensity = dimIntensity > 0.01 ? dimIntensity : 0.01;
        //print(0, String(dimIntensity));
	// update the lights
	analogWrite(redPin,  255 - curRed * dimIntensity * curIntensity);
	analogWrite(greenPin,255 - curGreen * dimIntensity * curIntensity);
	analogWrite(bluePin, 255 - curBlue * dimIntensity * curIntensity);
}
void processLed(){
        if(timeElapsed(processTime, processElapsed)){
                processTime = millis();
                processState = !processState;
                digitalWrite(processPin, processState);
        }
}


void writeToEEPROM(int number){
	// a base 256 number system is used to write to the EEPROM, because each EEPROM index can hold 256 values(it is a byte).
	// if the number is smaller than 256  
	if(number < 256){
		// write a 0 at index 0 for safety 
		EEPROM.write(0,0);
		// and write the number at index 1
		EEPROM.write(1,number); 
	}
	int mod = number % 256;
	if(mod == 0){
		// write the number divided by 256 at index 0
		EEPROM.write(0,number / 256);
		// write a 0 at index 1 for safety
		EEPROM.write(1,0);
		return; 
	}
	number - mod;
	// write what remains of the number, divided by 256 at index 0
	EEPROM.write(0,number / 256);
	// write what was left over at index 1
	EEPROM.write(1,mod);
}

int readFromEEPROM(){
	// read both values
	int a = EEPROM.read(0);
	int b = EEPROM.read(1);
	// combine the 2 using the base 256 system
	return 256 * a + b; 
}

int checkButtons()
{
	int buttons = analogRead(buttonPin) / 100;
	// Debounce
	if (buttons != lastButtonState) {
		// reset the debouncing timer
		lastDebounceTime = millis();
	}
	lastButtonState = buttons;
	if (timeElapsed(lastDebounceTime, debounceDelay))  {
		switch (buttons){ 
		case 10:
			//No buttons
			doorClosed = false;
			button1Pressed = false;
			button2Pressed = false;
			button3Pressed = false;
			break;
		case 7:
			//Door closed
			doorClosed = true;
			button1Pressed = false;
			button2Pressed = false;
			button3Pressed = false;
			break;
		case 6:
			//Button3
			button3Pressed = true;
			button1Pressed = false;
			button2Pressed = false;
			break;
		case 5:
			//Button2
			button2Pressed = true;
			button1Pressed = false;
			break;
		case 0:
			//Button1
			button1Pressed = true;
			break;
		} 
		return buttons;
	}
}
bool timeElapsed(unsigned long since, unsigned long elapsed){
	return (millis() - since > elapsed);
}

void motionChanged(){   
	motionDetected = digitalRead(motionSensor);
}

void distanceRecieved() {
	if (digitalRead(distanceSensorEcho))
		pingStart = micros();
	else{
		pingStop = micros();
		unsigned long duration = pingStop - pingStart;
		if(state == UNKNOWN || baselineDuration == -1){
			baselineDuration = duration;
		}
		lastDuration = duration;		
	}
}

void pingDistance(){
	if(timeElapsed(prevPing, pingDelay)){
		digitalWrite(distanceSensorTrigger,HIGH);
	        delayMicroseconds(10);
	        digitalWrite(distanceSensorTrigger,LOW);  
		prevPing = millis();
	}
}
