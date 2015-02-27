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
				break;
				numberOneTime = menuValue;
				menuSelect = false;
				break;
			case MENU_TIME:
				menuTime = menuValue;
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
				break;
			case EXIT:
                                startTime = millis() - (menuTime + 1);
                                menuSelect = false;
				break;
			}
		}
		else{
			//Select menuItem
			menuSelect = true;
		}
	}
	// Iterate items
	if (button3Pressed && !button3Prev) {
		button3Prev = true;
		startTime = millis();
		//This is a new click on the button
		if (menuSelect){
			if (menu == CLEANING_TIME || menu == NUMBER_ONE_TIME || menu == MENU_TIME || menu == DEGRADATION_TIME){
				//Increment menuValue
				menuValue += 10000; // increment of 10 seconds
				if (menuValue > 600000){ // maximum of 10 minutes 
					menuValue = 10000; // reset to 10 seconds
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
					if (menuValue > 2){ // Maximum lineNumber exceeded
						menuValue = 0; // Reset to first line
					}
				}
				else if (manual == 1){
					menuValue += 1; // Increment lineNumber
					if (menuValue > 10){ // Maximum lineNumber exceeded
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
					if (menuValue > 0){ // Maximum lineNumber exceeded
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
				menu = DEGRADATION_TIME;
				break;
			case DEGRADATION_TIME:
				menu = DEGRADATION;
				break;
			case DEGRADATION:
				menu = MANUAL;
				break;
			case MANUAL:
				menu = EXIT;
				break;
			case EXIT:
				menu = CLEANING_TIME;
				break;
			}
		}
	}
	//
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
		print(0, "Cleaning time:");
		if (menuSelect){
			print(1, "Change " + String(menuValue / 1000));
		}
		else{
			print(1, String(cleaningTime / 1000));
		}
		break;
	case NUMBER_ONE_TIME:
		print(0, "Number one time:");
		if (menuSelect){
			print(1, "Change " + String(menuValue / 1000));
		}
		else{
			print(1, String(numberOneTime / 1000));
		}
		break;
	case MENU_TIME:
		print(0, "Menu time:");
		if (menuSelect) {
			print(1, "Change " + String(menuValue / 1000));
		}
		else         {
			print(1, String(menuTime / 1000));
		}
		break;
	case DEGRADATION_TIME:
		print(0, "Degradation time:");
		if (menuSelect)          {
			print(1, "Change " + String(menuValue / 1000));
		}
		else          {
			print(1, String(degradationTime / 1000));
		}
		break;
	case DEGRADATION:
		print(0, "Degradation:");
		if (menuSelect){
			print(1, "Change " + String((menuValue == 1 ? "ON" : "OFF")));
		}
		else{
			print(1, degradation ? "ON" : "OFF");
		}
		break;
	case MANUAL:
		if (menuSelect){
			if (manual == 0){
				print(0, readmeOptions[menuValue]);
				if (menuValue < 2){
					print(1, readmeOptions[menuValue + 1]);
				}
				else{
					print(1, readmeOptions[0]);
				}
			}
			else if (manual == 1){
				print(0, readmeRGB[menuValue]);
				print(1, readmeRGB[menuValue + 1]);
			}
			else if (manual == 2){
				print(0, readmeTimers[menuValue]);
				print(1, readmeTimers[menuValue + 1]);
			}
                        else if (manual == 3){
				print(0, createdBy[menuValue]);
				print(1, createdBy[menuValue + 1]);
			}
		}
		else          {
			print(0, "Manual:");
			print(1, "Click to open!");
		}
		break;
	case EXIT:
		print(0, "Exit:");
		print(1, "Click to exit!");
		break;
	}
}
