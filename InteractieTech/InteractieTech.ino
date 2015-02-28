// Reinier Maas     - 4131495
// Björn Molenmaker - 3843874
#include <avr/pgmspace.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// State declaration
enum State {STANDBY, UNKNOWN, CLEANING, NUMBER_ONE, NUMBER_TWO, TRIGGERED, MENU};

//Define menu enumerable
enum Menu {CLEANING_TIME, NUMBER_ONE_TIME, MENU_TIME, SPRAY_TIME, NUMBER_ONE_SPRAYS, NUMBER_TWO_EXTRA_SPRAYS, TRIGGERED_SPRAYS, DEGRADATION_TIME, DEGRADATION, RESET, MANUAL, EXIT};

// README DECLARATION
const char readmeOptions_0[] PROGMEM = "readme RGB";//10
const char readmeOptions_1[] PROGMEM = "readme Timers";//13
const char readmeOptions_2[] PROGMEM = "readme Sprays";//13
const char readmeOptions_3[] PROGMEM = "created by";//10
const char *const readmeOptions[4] PROGMEM = {readmeOptions_0,readmeOptions_1,readmeOptions_2,readmeOptions_3 };

const char readmeRGB_0[] PROGMEM = "State color led";//15
const char readmeRGB_1[] PROGMEM = "Standby off";//11
const char readmeRGB_2[] PROGMEM = "Unknown white";//13
const char readmeRGB_3[] PROGMEM = "Cleaning green";//14
const char readmeRGB_4[] PROGMEM = "Menu blue";//9
const char readmeRGB_5[] PROGMEM = "#1 yellow";//9
const char readmeRGB_6[] PROGMEM = "#2 red";//6
const char readmeRGB_7[] PROGMEM = "TRIGGERED";//9
const char readmeRGB_8[] PROGMEM = "green flashing";//14
const char readmeRGB_9[] PROGMEM = " process trigger";//16
const char readmeRGB_10[] PROGMEM = "red flashing";//12
const char readmeRGB_11[] PROGMEM = " process #2";//11
const char readmeRGB_12[] PROGMEM = "yellow flashing";//15
const char readmeRGB_13[] PROGMEM = " process #1";//11
const char readmeRGB_14[] PROGMEM = "led on spraying";//15
const char *const readmeRGB[15] PROGMEM = {readmeRGB_0,readmeRGB_1,readmeRGB_2,readmeRGB_3,readmeRGB_4,readmeRGB_5,readmeRGB_6,readmeRGB_7,readmeRGB_8,readmeRGB_9,readmeRGB_10,readmeRGB_11,readmeRGB_12,readmeRGB_13,readmeRGB_14};

const char readmeTimers_0[] PROGMEM = "Timer looparound";//16
const char readmeTimers_1[] PROGMEM = "they start at 10";//16
const char readmeTimers_2[] PROGMEM = "seconds and end";//15
const char readmeTimers_3[] PROGMEM = "at 600 seconds,";//15
const char readmeTimers_4[] PROGMEM = "which is 10 min.";//16
const char *const readmeTimers[5] PROGMEM = {readmeTimers_0,readmeTimers_1,readmeTimers_2,readmeTimers_3,readmeTimers_4};

const char readmeSprays_0[] PROGMEM = "Spray looparound";//16
const char readmeSprays_1[] PROGMEM = "they start at 0";//15
const char readmeSprays_2[] PROGMEM = "sprays and end";//14
const char readmeSprays_3[] PROGMEM = "at 10 sprays.";//13
const char readmeSprays_4[] PROGMEM = "Together they";//13
const char readmeSprays_5[] PROGMEM = "reach 30 sprays.";//16
const char *const readmeSprays[6] PROGMEM = {readmeSprays_0,readmeSprays_1,readmeSprays_2,readmeSprays_3,readmeSprays_4,readmeSprays_5};

const char createdBy_0[] PROGMEM = "Reinier Maas";//12
const char createdBy_1[] PROGMEM = "Bjorn Molenmaker";//16
const char createdBy_2[] PROGMEM = "Interactie tech.";//16
const char createdBy_3[] PROGMEM = "2015 UU ICA";//11
const char *const createdBy[5] PROGMEM = {createdBy_0,createdBy_1,createdBy_2,createdBy_3,};

char buffer[16];
const char change[] = "Change ";
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
// analogue light port
const int lightPin = A0;
// analogue button port
const int buttonPin = A1;
// lcd ports (by label)
const int lcdD4 = A5;
const int lcdD5 = A4;
const int lcdD6 = A3;
const int lcdD7 = A2;

const int lcdRs = 4;
const int lcdEnable  = 8;
// Led backlight for LCD port
const int screenLED = 7;
// distance sensor pin
const int distanceSensorTrigger = 11;
const int distanceSensorEcho = 3;
// motion sensor pin
const int motionSensor = 2;
// Process led pin
const int processPin = 13;
// RGB led pins
const int bluePin = 9;
const int greenPin = 10;
const int redPin = 6;
// temperature sensor pin
const int temperaturePin = 12;
// mechanical actuator pin
const int actuator = 5;

// END OF PIN DECLARATIONS

// VARIABLE DECLARATIONS
unsigned long shotTime = -1;
unsigned long startTime,
        processTime,
        processElapsed = 100,
	cleaningTime = 30000,
	numberOneTime = 12000,
	degradationTime = 18000,
	shotDelay = 15000,
	menuTime = 60000,
	exitTime = 3000;
volatile bool tpUsed = false;
bool doorWasOpen = false;
bool degradation = true;
int degradated = 0;
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

// Process led
bool processState = HIGH;
// Motion Sensor
volatile bool motionDetected;

// Distance Sensor
volatile unsigned long pingStart = 0; // Holds the ping start time.
volatile unsigned long pingStop; // Holds the ping stop time.
unsigned long prevPing = 0;
volatile unsigned long lastDuration; // Holds calculated distance of the ping.
volatile unsigned long baselineDuration = -1;
unsigned long pingDelay = 500;

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
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;
int lastButtonState = 7;

// Menu last button state
bool button2Prev = false;
bool button3Prev = false;
// Menu Select
bool menuSelect = false;
unsigned long menuValue = 10000;
int manual = 0;
unsigned long menuExit = 0; 

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
        // set the process pin as output
        pinMode(processPin, OUTPUT);
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
        //Processing led
        processLed();
        // ButtonCheck
        checkButtons();
        //LightCheck
        dimLight();
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
                        print(0, "t: " + String(t) + "%0C SR: " + String(shotsRemaining));       
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
