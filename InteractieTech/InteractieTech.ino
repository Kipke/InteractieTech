// Reinier Maas     - 4131495
// Björn Molenmaker - 3843874

#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// State declaration
enum State {STANDBY, UNKNOWN, CLEANING, NUMBER_ONE, NUMBER_TWO, TRIGGERED, MENU};

//Define menu enumerable
enum Menu {CLEANING_TIME, NUMBER_ONE_TIME, MENU_TIME, SPRAY_TIME, NUMBER_ONE_SPRAYS, NUMBER_TWO_EXTRA_SPRAYS, TRIGGERED_SPRAYS, DEGRADATION_TIME, DEGRADATION, RESET, MANUAL, EXIT};

// README DECLARATION
String readmeOptions[3] = { "readme RGB",
        "readme Timers",
	"created by" };
String readmeRGB[12] = {"State color led",
	"Standby off",
	"Unknown white",
	"Cleaning green",
	"Menu blue",
	"#1 yellow",
	"#2 red",
	"Triggered",
	"yellow flashing",
	"    1 remaining",
	"red flashing",
	"    2 remaining" };
String readmeTimers[5] = {"Timer looparound",
        "they start at 10",
        "seconds and end",
        "at 600 seconds", 
        "which is 10 min."};
String createdBy[2] = { "Reinier Maas",
	"Bjorn Molenmaker" };

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

// analogue button port
int buttonPin = A1;
// lcd ports (by label)
int lcdD4 = A5;
int lcdD5 = A4;
int lcdD6 = A3;
int lcdD7 = A2;

int lcdRs = 4;
int lcdEnable  = 8;
// Led backlight for LCD port
int screenLED = 7;
// distance sensor pin
const int distanceSensorTrigger = 11;
const int distanceSensorEcho = 3;
// motion sensor pin
int motionSensor = 2;
// RGB led pins
int bluePin = 9;
int greenPin = 10;
int redPin = 6;
// temperature sensor pin
int temperaturePin = 12;
// mechanical actuator pin
int actuator = A0;

// END OF PIN DECLARATIONS

// VARIABLE DECLARATIONS
long shotTime = -1;
long startTime,
	cleaningTime = 30000,
	numberOneTime = 12000,
	degradationTime = 18000,
	shotDelay = 15000,
	menuTime = 60000,
	exitTime = 3000;
volatile bool tpUsed = false;
bool doorWasOpen = false;
bool degradation = true;
bool fireNumberOne = false;
bool fireNumberTwo = false;
bool fireTriggered = false;
int numberOneShots = 1;
int numberTwoShots = 1;
int triggeredShots = 1;
int shotsToFireNumberOne = 0;
int shotsToFireNumberTwo = 0;
int shotsToFireTriggered = 0;
int shotsRemaining;
int temperature;

// Motion Sensor
bool motionDetected;

// Distance Sensor
volatile unsigned long pingStart = 0; // Holds the ping start time.
volatile unsigned long pingStop; // Holds the ping stop time.
long prevPing = 0;
volatile int lastDistance; // Holds calculated distance of the ping.
volatile int baselineDistance = -1;
volatile int pingDelay = 500;

// the state as defined above
State state;
// the menu as defined aboce
Menu menu;

// lcd initialization
LiquidCrystal lcd(lcdRs, lcdEnable, lcdD4, lcdD5, lcdD6, lcdD7);

// variables for the temperature
OneWire oneWire(temperaturePin);
DallasTemperature sensors(&oneWire);
DeviceAddress thermometer;

// Button declaration
bool doorClosed = true;
bool button1Pressed = false; //Spray
bool button2Pressed = false; //Menu
bool button3Pressed = false; //Next
//Button debounce
long lastDebounceTime = 0;
long debounceDelay = 50;
int lastButtonState = 7;

// Menu last button state
bool button2Prev = false;
bool button3Prev = false;
// Menu Select
bool menuSelect = false;
long menuValue = 10000;
int manual = 0;
long menuExit = 0; 

// END OF VARIABLE DECLARATIONS

void setup() {
	// put your setup code here, to run once:

	// start the serial monitor
	Serial.begin(9600);
	// Set the initial menu to cleaning_time
	menu = CLEANING_TIME;
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
	// Distance
	pinMode(distanceSensorEcho,INPUT);
	pinMode(distanceSensorTrigger,OUTPUT);
	attachInterrupt(distanceSensorEcho - 2, distanceRecieved, CHANGE);
	// setup the motion sensor and its interrupt
	pinMode(motionSensor,INPUT);
	attachInterrupt(motionSensor - 2, motionChanged,CHANGE);
	// initialize the motionDetected variable
	motionDetected = digitalRead(motionSensor);
	// read the remaining shots from the EEPROM
	shotsRemaining = readFromEEPROM();
	// Set the initial state to standby
	state = STANDBY;
}

void loop() {
        // put your main code here, to run repeatedly:

        // Code that has to be done regardless of state
        // ButtonCheck
        checkButtons();
        // if the dedicated spray button is pressed
	if (button1Pressed){
                // set the amount of shots to fire
                fireTriggered = true;
                shotsToFireTriggered = triggeredShots;
                // start the degradation timer
		degradationTime = millis();
                // set the state to triggered
                state = TRIGGERED;                
	}
        if(state != MENU){
                if (button2Pressed && timeElapsed(menuExit, exitTime)){
                        // Menu enter
                        startTime = millis();
                        state = MENU;
                        button2Prev = true;
                }
                else
                {
                        // Temperature  and shots remaining update
                        sensors.requestTemperatures();
                        int t = sensors.getTempC(thermometer);
                        String s1 = "t: ";
                        String s3 = s1 + t + "%0C SR: " + shotsRemaining;      
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
                    //print(1,"menu");
                    break;
        }
}
