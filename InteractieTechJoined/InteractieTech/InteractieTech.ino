//LCD
#include <LiquidCrystal.h>
//Temperature
//#include <OneWire.h>
//#include <DallasTemperature.h>
//#define ONE_WIRE_BUS 12

//Define state enumerable
enum State {STANDBY, UNKNOWN, CLEANING, NUMBER_ONE, NUMBER_TWO, TRIGGERED, MENU};

//Define menu enumerable
enum Menu {CLEANING_TIME, NUMBER_ONE_TIME, NUMER_TWO_TIME, DEGRADATION_TIME, DEGRADATION, MANUAL};

// Set the initial state to standby
State state = STANDBY;

// Set the inital menu to CLEANING
Menu menu = CLEANING_TIME;

//LCD
LiquidCrystal lcd(4, 2, A5, A4, A3, A2);
const int backLight = 3;

//Temperature
//OneWire oneWire(ONE_WIRE_BUS);
//DallasTemperature sensors(&oneWire);
//DeviceAddress thermometer;

//Distance
const int distance = 7;

//Movement
const int movement = 8;

//Light
const int light = A0;

//Buttons
const int buttons = A1;

//State variables
//Unknown
bool unknownFirst = true;
long unknownTimer = 0;
long unknownTime = 5 * 60 * 1000;
//NumberOne
bool number_oneFirst = true;
long number_oneTimer = 0;
long number_oneTime = 2 * 60 * 1000;
//Triggered
int shotsToFire = 0;
bool degradationFirst = true;
long degradationTimer = 0;
long degradationTime = 3 * 60 * 1000;
//Menu
bool menuFirst = true;
long menuTimer = 0;
long menuTime = 1 * 60 * 1000;

void setup() {
  // put your setup code here, to run once:
  setupLCD();
  setupMovement();
  setupLight();
  setupButtons();
  //setupTemperature();
}
void setupLCD()
{
  lcd.begin(16, 2);
  lcd.print("di m    li bu");
  pinMode(backLight, OUTPUT);
  digitalWrite(backLight, LOW);
}
void setupMovement()
{
  pinMode(movement, INPUT);
}
void setupLight()
{
  pinMode(light, INPUT);
}
void setupButtons()
{
  pinMode(buttons, INPUT);
}
void setupTemperature()
{
  //sensors.begin();
  //sensors.getAddress(thermometer, 0);
  //sensors.setResolution(thermometer, 9);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (loopButtons() / 100 == 0)
    state = MENU;
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
  if(loopButtons() / 100 == 10 || loopMovement() == 1)
    state = UNKNOWN;
}

void unknownActions(){
  // light is white
  // start timer
  if (unknownFirst)
  {
    unknownFirst = false;
    unknownTimer = millis();
  }
  // if door closes
  if (loopButtons() / 100 == 10)
  {
    unknownFirst = true;
    state = NUMBER_ONE;
  }
  // if time > x
  if (unknownTimer - millis() > unknownTime)
  {
    unknownFirst = true;
    state = CLEANING;
  }
}

void cleaningActions(){
  // light is green
  // if door closed or no movement
  if(loopButtons() / 100 == 7 || loopMovement() == 0)
    state = STANDBY;
}

void number_oneActions(){
  // light is yellow
  // start timer
  if (number_oneFirst)
  {
    number_oneFirst = false;
    number_oneTimer = millis();
  }
  // if door opens or no movement
  if(loopButtons() / 100 == 10 || loopMovement() == 0)
    number_oneFirst = true;
    shotsToFire = 1;
    state = TRIGGERED;
  // if toilet paper used
  //   tpUsed = true;
  // if time > y and tpUsed
  if (number_oneTimer - millis() > number_oneTime)
  {
    number_oneFirst = true;
    state = NUMBER_TWO;
  }
}

void number_twoActions(){
  // light is red/brown
  // if door opens or no movement
  if(loopButtons() / 100 == 10 || loopMovement() == 0)
    shotsToFire = 2;
    state = TRIGGERED;
}

void triggeredActions(){
  // light is flashing color of shots remaining
  // degradation timer and shots to fire magic :-)
  // start timer
  if (degradationFirst)
  {
    degradationFirst = false;
    degradationTimer = millis();
  }
  // if time > x
  if (degradationTimer - millis() > degradationTime)
  {
    degradationFirst = true;
    if (shotsToFire == 2)
      shotsToFire = 1;
  }
  // if door closed or no movement
  if(loopButtons() / 100 == 7 || loopMovement() == 0)
    fire(shotsToFire);
  //  start shot countdown
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

//Spuitbus
void fire(int shotsToFire)
{
  
}

//Sensor readings
float loopTemperature()
{
  //sensors.requestTemperatures();
  //return sensors.getTempC(thermometer);
}

int loopMovement()
{
  return digitalRead(movement);
}

int loopLight()
{
  return analogRead(light);
}

int loopButtons()
{
  return analogRead(buttons);
}

long loopDistance()
{
  long duration, cm;
  pinMode(distance, OUTPUT);
  digitalWrite(distance, LOW);
  delayMicroseconds(5);
  digitalWrite(distance, HIGH);
  delayMicroseconds(10);
  digitalWrite(distance, LOW);
  pinMode(distance, INPUT);
  duration = pulseIn(distance, HIGH);
  cm = duration / 29 / 2;
  return cm;
}
