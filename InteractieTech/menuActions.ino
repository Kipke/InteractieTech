void menuActions(){
  // light is blue
  lightColor(0,0,255);
  // Show manual
  
  // Exit timer
  if (timeElapsed(startTime, menuExit)){
    state = STANDBY;
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
    //This is a new click on the button
    if (menuSelect)
    {
      //Save menuValue to corresponding variable
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
    //This is a new click on the button
    if (menuSelect)
    {
      //Increment menuValue
      menuValue += 10000; // increment of 10 seconds
      if (menuValue > 600000) // maximum of 10 minutes 
        menuValue = 10000; // reset to 10 seconds
    }
    else
    {
      //Iterate menuItem
      //enum Menu {CLEANING_TIME, NUMBER_ONE_TIME, NUMER_TWO_TIME, DEGRADATION_TIME, DEGRADATION, MANUAL};
      switch (menu)
      {
        case CLEANING_TIME:
          menu = NUMBER_ONE_TIME;
          break;
        case NUMBER_ONE_TIME:
          menu = NUMER_TWO_TIME;
          break;
        case NUMER_TWO_TIME:
          menu = DEGRADATION_TIME;
          break;
        case DEGRADATION_TIME:
          menu = DEGRADATION;
          break;
        case DEGRADATION:
          menu = MANUAL;
          break;
        case MANUAL:
          menu = CLEANING_TIME;
          break;
      }
    }
  }
  //Print on lcd
}
