#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <OneWire.h>
#include <DallasTemperature.h>

enum State {STANDBY, UNKNOWN, CLEANING, NUMBER_ONE, NUMBER_TWO, TRIGGERED, MENU};
State state;

LiquidCrystal lcd(6, 4, A2, A3, A4, A5);

byte degree[8] = {
  B01000,
  B10100,
  B01000,
  B00000,
  B00000,
  B00000,
  B00000,
};

int screenLED = 5;
int buttonPin = A1;

int temperaturePin = 12;

int redPin = 11;
int greenPin = 10;
int bluePin = 9;

int startTime, degradationTime, shotTime = -1;
int x = 30, y = 12, z = 18 , w = 5, shotDelay = 15;
bool tpUsed = false;
int shotsToFire;
int shotsRemaining;
int temperature;

// variables for the temperature
OneWire oneWire(temperaturePin);
DallasTemperature sensors(&oneWire);
DeviceAddress thermometer;

void setup() {
  // put your setup code here, to run once:
  
  // start the serial monitor
  Serial.begin(9600);
  // Set the initial state to standby
  state = STANDBY;
  // Set the LCD backlight as an output
  pinMode(screenLED,OUTPUT);
  // Set the actuater pin as an output
  pinMode(13,OUTPUT);
  // set the color pins as outputs
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(9,OUTPUT);
  // set up the LCD's number of columns and rows:
  lcd.createChar(0,degree);
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
  if(state != MENU){
    sensors.requestTemperatures();
    int t = sensors.getTempC(thermometer);
    if(t != temperature){
      String s1 = "Temp: ";
      String s3 = s1 + t + "D-C";      
      print(0,s3); 
    }
  } 
  
  int v = analogRead(buttonPin);
  //char s[32];
  //sprintf(s,"%i",v);
  //print(0, s);  
  
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






