void menuActions(){
  // light is blue
  lightColor(0,0,255);
  // Exit timer
  if (timeElapsed(startTime, menuTime)){
    state = STANDBY;
    startTime = millis();
  }
  // Manage button press
  // if button was used last check can't be used again untill returned to false
  if (!button2Pressed)
    button2Prev = false;
  if (!button3Pressed)
    button3Prev = false;
  // Select item
  if (button2Pressed && ! button2Prev)
  {
    button2Prev = true;
    startTime = millis();
    //This is a new click on the button
    if (menuSelect)
    {
      switch (menu)
      {
        case CLEANING_TIME:
          cleaningTime = menuValue;
          break;
        case NUMBER_ONE_TIME:
          break;
          numberOneTime = menuValue;
          break;
        case MENU_TIME:
          menuTime = menuValue;
          break;
        case DEGRADATION_TIME:
          degradationTime = menuValue;
          break;
        case DEGRADATION:
          degradation = menuValue == 1;
          break;
        case MANUAL:
          break;
      }
      menuSelect = false;
    }
    else
    {
      //Select menuItem
      menuSelect = true;
    }
  }
  // Iterate items
  if (button3Pressed && !button3Prev)
  {
    button3Prev = true;
    startTime = millis();
    //This is a new click on the button
    if (menuSelect)
    {
      if (menu == CLEANING_TIME || menu == NUMBER_ONE_TIME || menu == MENU_TIME || menu == DEGRADATION_TIME)
      {
        //Increment menuValue
        menuValue += 10000; // increment of 10 seconds
        if (menuValue > 600000) // maximum of 10 minutes 
          menuValue = 10000; // reset to 10 seconds
      }
      else if (menu == DEGRADATION)
      {
        // Change menuValue
        menuValue += 1; // False to true
        if (menuValue > 1) // Maximum of true
          menuValue = 0; // Reset to false
      }
      else if (menu == MANUAL)
      {
        // Keep lineNumber in check
        menuValue += 1; // Increment lineNumber
        if (menuValue > 0) // Maximum lineNumber exceeded
          menuValue = 0; // Reset to first line
      }
    }
    else
    {
      //Iterate menuItem
      //enum Menu {CLEANING_TIME, NUMBER_ONE_TIME, MENU_TIME, DEGRADATION_TIME, DEGRADATION, MANUAL};
      switch (menu)
      {
        case CLEANING_TIME:
          menu = NUMBER_ONE_TIME;
          menuValue = cleaningTime;
          break;
        case NUMBER_ONE_TIME:
          menu = MENU_TIME;
          menuValue = numberOneTime;
          break;
        case MENU_TIME:
          menu = DEGRADATION_TIME;
          menuValue = menuTime;
          break;
        case DEGRADATION_TIME:
          menu = DEGRADATION;
          menuValue = degradationTime;
          break;
        case DEGRADATION:
          menu = MANUAL;
          menuValue = degradation ? 1 : 0;
          break;
        case MANUAL:
          menu = CLEANING_TIME;
          break;
      }
    }
  }
  //Print on lcd
  switch (menu)
      {
        case CLEANING_TIME:
          print(0, "Cleaning time:");
          if (menuSelect)
          {
            print(1, "Change " + String(menuValue / 1000));
          }
          else
          {
            print(1, String(cleaningTime / 1000));
          }
          break;
        case NUMBER_ONE_TIME:
          print(0, "Number one time:");
          if (menuSelect)
          {
            print(1, "Change " + String(menuValue / 1000));
          }
          else
          {
            print(1, String(numberOneTime / 1000));
          }
          break;
        case MENU_TIME:
          print(0, "Menu time:");
          if (menuSelect)
          {
            print(1, "Change " + String(menuValue / 1000));
          }
          else
          {
            print(1, String(menuTime / 1000));
          }
          break;
        case DEGRADATION_TIME:
          print(0, "Degradation time:");
          if (menuSelect)
          {
            print(1, "Change " + String(menuValue / 1000));
          }
          else
          {
            print(1, String(degradationTime / 1000));
          }
          break;
        case DEGRADATION:
          print(0, "Degradation:");
          if (menuSelect)
          {
            print(1, "Change " + String((menuValue == 1 ? "ON" : "OFF")));
          }
          else
          {
            print(1, degradation ? "ON" : "OFF");
          }
          break;
        case MANUAL:
          if (menuSelect)
          {
            //TODO write manual
            print(1, "Click to close!");
          }
          else
          {
            print(0, "Manual:");
            print(1, "Click to open!");
          }
          break;
      }
}
