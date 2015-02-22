#include <LiquidCrystal.h>

enum State {STANDBY, UNKNOWN, CLEANING, NUMBER_ONE, NUMBER_TWO, TRIGGERED, MENU};
State state;

LiquidCrystal lcd(6, 4, A2, A3, A4, A5);

int screenLED = 5;
int buttonPin = A1;

int startTime, degradationTime, shotTime = -1;
int x = 300, y = 120, z = 180 , w = 5, shotDelay = 15;
bool tpUsed = false;
int shotsToFire;

void setup() {
  // put your setup code here, to run once:
  
  // Set the initial state to standby
  state = STANDBY;
  // Set the LCD backlight as an output
  pinMode(screenLED,OUTPUT);
  pinMode(13,OUTPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

}

void loop() {
  // put your main code here, to run repeatedly:
  //digitalWrite(screenLED,HIGH);
  int v = analogRead(buttonPin);
  char s[32];
  sprintf(s,"%i",v);
  print(0, s);  
  
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




