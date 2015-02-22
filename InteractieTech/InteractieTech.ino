enum State {STANDBY, UNKNOWN, CLEANING, NUMBER_ONE, NUMBER_TWO, TRIGGERED, MENU};

State state;

void setup() {
  // put your setup code here, to run once:
  
  // Set the initial state to standby
  state = STANDBY;

}

void loop() {
  // put your main code here, to run repeatedly:
  // Check which state we are in and then perform the actions related to that state
  switch(state){    
    case STANDBY:
      standbyActions();
      break;
    case UNKNOWN:
      unknownActions();
      break;
    case CLEANING:
      cleaningActions();
      break;
    case NUMBER_ONE:
      number_oneActions();
      break;
    case NUMBER_TWO:
      number_twoActions();
      break;
    case TRIGGERED:
      triggeredActions();
      break;
    case MENU:
      menuActions();
      break;
  }
}

void standbyActions(){
  // light is off
  // if motion or door
  //   state = UNKNOWN;
}
void unknownActions(){
  // light is white
  // start timer
  // if door closes
  //   state = NUMBER_ONE;
  // if time > x
  //   state = CLEANING;
}
void cleaningActions(){
  // light is green
  // if door closed or no movement
  //   state = STANDBY;  
}
void number_oneActions(){
  // light is yellow
  // if door opens or no movement
  //   shotsToFire = 1;
  //   state = TRIGGERED;
  //   degradation timer started
  // if toilet paper used
  //   tpUsed = true;
  // if time > y and tpUsed
  //   state = NUMBER_TWO;
}
void number_twoActions(){
  // light is red/brown
  // if door opens or no movement
  //   shotsToFire = 2;
  //   state = TRIGGERED;  
  //   degradation timer started 
}
void triggeredActions(){
  // light is flashing color of shots remaining
  // degradation timer and shots to fire magic :-)
  // if no movement
  //   start shot countdown
  // if shot countdown == 0
  //   fire shot;
  //   shotsToFire--;
  // if shotsToFire == 0
  //   state = STANDBY;
}
void menuActions(){
  // light is blue
  // TODO
}

