#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// State declaration
enum State {STANDBY, UNKNOWN, CLEANING, NUMBER_ONE, NUMBER_TWO, TRIGGERED, MENU};

// CUSTOM CHARACTER DECLARATIONS
byte degree[8] = {
  B01000,
  B10100,
  B01000,
  B00000,
  B00000,
  B00000,
  B00000,
};
// END OF CUSTOM CHARACTER DECLARATIONS

// PIN DECLARATIONS

// light sensor port
int lightSensor = A0;
// analogue button port
int buttonPin = A1;
// lcd ports (by label)
int lcdD4 = A5;
int lcdD5 = A4;
int lcdD6 = A3;
int lcdD7 = A2;

int lcdRs = 4;
int lcdEnable  = 2;
// Led backlight for LCD port
int screenLED = 3;
// distance sensor pin
int distanceSensor = 7;
// motion sensor pin
int motionSensor = 8;
// RGB led pins
int bluePin = 9;
int greenPin = 10;
int redPin = 11;
// temperature sensor pin
int temperaturePin = 12;
// mechanical actuator pin
int actuator = 13;

// END OF PIN DECLARATIONS

// VARIABLE DECLARATIONS
int startTime, degradationTime, shotTime = -1;
long x = 30000, y = 12000, z = 18000, w = 5000, shotDelay = 15;
bool tpUsed = false;
int shotsToFire;
int shotsRemaining;
int temperature;

// the state as defined above
State state;

// lcd initialization
LiquidCrystal lcd(lcdRs, lcdEnable, lcdD4, lcdD5, lcdD6, lcdD7);

// variables for the temperature
OneWire oneWire(temperaturePin);
DallasTemperature sensors(&oneWire);
DeviceAddress thermometer;

//Button declaration
bool doorClosed;
bool button1Pressed; //Spray
bool button2Pressed; //Menu
bool button3Pressed; //Next

// END OF VARIABLE DECLARATIONS

void setup() {
  // put your setup code here, to run once:
  
  // start the serial monitor
  Serial.begin(9600);
  // Set the initial state to standby
  state = STANDBY;
  // Set the LCD backlight as an output
  pinMode(screenLED,OUTPUT);  
  // Set the actuater pin as an output
  pinMode(actuator,OUTPUT);  
  // set the color pins as outputs
  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);  
  // create the custom degree character
  lcd.createChar(0,degree);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);    
  // setup the temperature sensor
  sensors.begin();
  if (!sensors.getAddress(thermometer, 0)){
    Serial.println("Unable to find address for Device 0");
  }  
  sensors.setResolution(thermometer, 9);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // Code that has to be done regardless of state (with the exception of the menu)
  // ButtonCheck
  checkButtons();
  // Temperature update
  if(state != MENU){
    sensors.requestTemperatures();
    int t = sensors.getTempC(thermometer);
    if(t != temperature){
      String s1 = "Temp: ";
      String s3 = s1 + t + "D-C";      
      print(0,s3); 
    }
  }     
  // Check which state we are in and then perform the actions related to that state
  switch(state){    
    case STANDBY:
      standbyActions();
      print(1,"standby");
      break;
    case UNKNOWN:
      unknownActions();
      print(1,"unknown");
      break;
    case CLEANING:
      cleaningActions();
      print(1,"cleaning");
      break;
    case NUMBER_ONE:
      number_oneActions();
      print(1,"#1");
      break;
    case NUMBER_TWO:
      number_twoActions();
      print(1,"#2");
      break;
    case TRIGGERED:
      triggeredActions();
      print(1,"triggered");
      break;
    case MENU:
      menuActions();
      print(1,"menu");
      break;
  }
}






