// Reinier Maas     - 4131495
// Björn Molenmaker - 3843874

void menuActions(){
        // light is blue
	lightColor(0,0,255);
	// turn screen backlight on
	digitalWrite(screenLED, HIGH);
	// Exit timer
	if (timeElapsed(startTime, menuTime)){
		state = STANDBY;
		startTime = millis();
                menuExit = millis();
		print(0, "");
		print(1, "");
	}
	// Manage button press
	// if button was used last check can't be used again untill returned to false
	if (!button2Pressed){
		button2Prev = false;
	}
	if (!button3Pressed){
		button3Prev = false;
	}
	// Select item
	if (button2Pressed && ! button2Prev) {
		button2Prev = true;
		startTime = millis();
		//This is a new click on the button
		if (menuSelect){
			switch (menu){
			case CLEANING_TIME:
				cleaningTime = menuValue;
				menuSelect = false;
				break;
			case NUMBER_ONE_TIME:
				numberOneTime = menuValue;
				menuSelect = false;
				break;
			case MENU_TIME:
				menuTime = menuValue;
				menuSelect = false;
				break;
                        case SPRAY_TIME:
                                shotDelay = menuValue;
				menuSelect = false;
				break;
                        case NUMBER_ONE_SPRAYS:
                                numberOneShots = menuValue;
				menuSelect = false;
                                break;
                        case NUMBER_TWO_EXTRA_SPRAYS:
                                numberTwoShots = menuValue;
				menuSelect = false;
				break;
                        case TRIGGERED_SPRAYS:
                                triggeredShots = menuValue;
				menuSelect = false;
				break;
			case DEGRADATION_TIME:
				degradationTime = menuValue;
				menuSelect = false;
				break;
			case DEGRADATION:
				degradation = menuValue == 1;
				menuSelect = false;
				break;
			case MANUAL:
				if (manual == 0){
					manual = menuValue + 1;
					menuValue = 0;
				}
				else{
					menuSelect = false;
				}
			}
		}
		else{
			switch (menu){
                                case RESET:
                                        writeToEEPROM(2400);
                                        shotsRemaining = 2400;
                                        menuSelect = false;
                                        break;
                                case EXIT:
                                        startTime = millis() - (menuTime + 1);
                                        menuSelect = false;
                                        break;
	                        default://Select menuItem
                                        menuSelect = true;
                        }
		}
	}
	// Iterate items
	if (button3Pressed && !button3Prev) {
		button3Prev = true;
		startTime = millis();
		//This is a new click on the button
		if (menuSelect){
			if (menu == CLEANING_TIME || menu == NUMBER_ONE_TIME || menu == MENU_TIME || menu == SPRAY_TIME|| menu == DEGRADATION_TIME){
				//Increment menuValue
				menuValue += 10000; // increment of 10 seconds
				if (menuValue > 600000){ // maximum of 10 minutes 
					menuValue = 10000; // reset to 10 seconds
				}
			}
                        else if (menu == NUMBER_ONE_SPRAYS || menu == NUMBER_TWO_EXTRA_SPRAYS || menu == TRIGGERED_SPRAYS){
                                //Increment menuValue
				menuValue += 1; // increment of 1 spray
				if (menuValue > 10){ // maximum of 10 sprays 
					menuValue = 0; // reset to 0 sprays
				}
                        }
			else if (menu == DEGRADATION){
				// Change menuValue
				menuValue += 1; // False to true
				if (menuValue > 1){ // Maximum of true
					menuValue = 0; // Reset to false
				}
			}
			else if (menu == MANUAL){
				// Keep lineNumber in check
				if (manual == 0){
					menuValue += 1; // Increment lineNumber
					if (menuValue > 3){ // Maximum lineNumber exceeded
						menuValue = 0; // Reset to first line
					}
				}
				else if (manual == 1){
					menuValue += 1; // Increment lineNumber
					if (menuValue > 13){ // Maximum lineNumber exceeded
						menuValue = 0; // Reset to first line
					}
				}
				else if (manual == 2){
					menuValue += 1; // Increment lineNumber
					if (menuValue > 3){ // Maximum lineNumber exceeded
						menuValue = 0; // Reset to first line
					}
				}
                                else if (manual == 3){
					menuValue += 1; // Increment lineNumber
					if (menuValue > 4){ // Maximum lineNumber exceeded
						menuValue = 0; // Reset to first line
					}
				}
                                else if (manual == 4){
					menuValue += 1; // Increment lineNumber
					if (menuValue > 2){ // Maximum lineNumber exceeded
						menuValue = 0; // Reset to first line
					}
				}
			}
		}
		else{
			//Iterate menuItem
			//enum Menu {CLEANING_TIME, NUMBER_ONE_TIME, MENU_TIME, DEGRADATION_TIME, DEGRADATION, MANUAL};
			switch (menu){
			case CLEANING_TIME:
				menu = NUMBER_ONE_TIME;
				break;
			case NUMBER_ONE_TIME:
				menu = MENU_TIME;
				break;
			case MENU_TIME:
				menu = SPRAY_TIME;
				break;
			case SPRAY_TIME:
				menu = NUMBER_ONE_SPRAYS;
				break;
			case NUMBER_ONE_SPRAYS:
				menu = NUMBER_TWO_EXTRA_SPRAYS;
				break;
			case NUMBER_TWO_EXTRA_SPRAYS:
				menu = TRIGGERED_SPRAYS;
				break;
			case TRIGGERED_SPRAYS:
				menu = DEGRADATION_TIME;
				break;
			case DEGRADATION_TIME:
				menu = DEGRADATION;
				break;
			case DEGRADATION:
				menu = RESET;
				break;
			case RESET:
				menu = MANUAL;
				break;
			case MANUAL:
				menu = EXIT;
				break;
			case EXIT:
				menu = CLEANING_TIME;
			}
		}
	}
	// Make sure the menuValue is updated
	if (!menuSelect){
		switch (menu){
		case CLEANING_TIME:
			menuValue = cleaningTime;
			break;
		case NUMBER_ONE_TIME:
			menuValue = numberOneTime;
			break;
		case MENU_TIME:
			menuValue = menuTime;
			break;
        	case SPRAY_TIME:
        		menuValue = shotDelay;
        		break;
        	case NUMBER_ONE_SPRAYS:
        		menuValue = numberOneShots;
        		break;
        	case NUMBER_TWO_EXTRA_SPRAYS:
        		menuValue = numberTwoShots;
        		break;
        	case TRIGGERED_SPRAYS:
        		menuValue = triggeredShots;
        		break;
	        case DEGRADATION_TIME:
			menuValue = degradationTime;
			break;
		case DEGRADATION:
			menuValue = degradation ? 1 : 0;
			break;
		case MANUAL:
                        manual = 0;
			menuValue = 0;
			break;
		}
	}
	//Print on lcd
	switch (menu){
	case CLEANING_TIME:
		printMenu("Cleaning time", 1000);
		break;
	case NUMBER_ONE_TIME:
		printMenu("#1 time", 1000);
		break;
	case MENU_TIME:
		printMenu("Menu time", 1000);
		break;
	case SPRAY_TIME:
		printMenu("Spray delay", 1000);
		break;
	case NUMBER_ONE_SPRAYS:
		printMenu("#1 Sprays", 1);
		break;
	case NUMBER_TWO_EXTRA_SPRAYS:
		printMenu("#2 Extra sprays", 1);
		break;
	case TRIGGERED_SPRAYS:
		printMenu("Triggered sprays", 1);
		break;
	case DEGRADATION_TIME:
		printMenu("Degradation time", 1000);
		break;
	case DEGRADATION:
		print(0, "Degradation");
		if (menuSelect){
			print(1, change + String((menuValue == 1 ? "ON" : "OFF")));
		}
		else{
			print(1, degradation ? "ON" : "OFF");
		}
		break;
        case RESET:
		print(0, "Reset");
		print(1, "Spray count " + String(shotsRemaining));
		break;
	case MANUAL:
		if (menuSelect){
			if (manual == 0){
                                strcpy_P(buffer, (char*)pgm_read_word(&(readmeOptions[menuValue])));
				print(0, buffer);
				if (menuValue < 3){
					strcpy_P(buffer, (char*)pgm_read_word(&(readmeOptions[menuValue + 1])));
				        print(1, buffer);
				}
				else{
					strcpy_P(buffer, (char*)pgm_read_word(&(readmeOptions[0])));
				        print(1, buffer);
				}
			}
			else if (manual == 1){
				strcpy_P(buffer, (char*)pgm_read_word(&(readmeRGB[menuValue])));
                                print(0, buffer);
				strcpy_P(buffer, (char*)pgm_read_word(&(readmeRGB[menuValue + 1])));
                                print(1, buffer);
			}
			else if (manual == 2){
				strcpy_P(buffer, (char*)pgm_read_word(&(readmeTimers[menuValue])));
                                print(0, buffer);
				strcpy_P(buffer, (char*)pgm_read_word(&(readmeTimers[menuValue + 1])));
                                print(1, buffer);
			}
			else if (manual == 3){
				strcpy_P(buffer, (char*)pgm_read_word(&(readmeSprays[menuValue])));
                                print(0, buffer);
				strcpy_P(buffer, (char*)pgm_read_word(&(readmeSprays[menuValue + 1])));
                                print(1, buffer);
			}
                        else if (manual == 4){
				strcpy_P(buffer, (char*)pgm_read_word(&(createdBy[menuValue])));
                                print(0, buffer);
				strcpy_P(buffer, (char*)pgm_read_word(&(createdBy[menuValue + 1])));
                                print(1, buffer);
			}
		}
		else          {
			print(0, "Manual");
			print(1, "Open");
		}
		break;
	case EXIT:
		print(0, "Exit");
		print(1, "Menu");
		break;
	}
}
