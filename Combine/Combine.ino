//LCD
#include <LiquidCrystal.h>
//Temperature
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 12

//LCD
LiquidCrystal lcd(11, 10, 5, 4, 3, 2);

//Temperature
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress thermometer;

//Distance
const int distance = 8;

//Movement
const int movement = 7;

//Light
int light = A0;

//Buttons
int buttons = A1;

void setup()
{
  setupLCD();
  setupMovement();
  setupLight();
  setupButtons();
  setupTemperature();
}
void setupLCD()
{
  lcd.begin(16, 2);
  lcd.print("di m te li bu");
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
  sensors.begin();
  sensors.getAddress(thermometer, 0);
  sensors.setResolution(thermometer, 9);
}

void loop()
{
  //LCD
  lcd.setCursor(0, 1);
  lcd.print("    ");
  lcd.setCursor(0, 1);
  lcd.print(loopDistance());
  lcd.setCursor(3, 1);
  lcd.print(loopMovement());
  lcd.setCursor(5, 1);
  lcd.print(loopTemperature());
  lcd.setCursor(7, 1);
  lcd.print("         ");
  lcd.setCursor(8, 1);
  lcd.print(loopLight() / 10);
  lcd.setCursor(11, 1);
  lcd.print(loopButtons() / 100);
}
float loopTemperature()
{
  sensors.requestTemperatures();
  return sensors.getTempC(thermometer);
}
int loopMovement()
{
  return digitalRead(movement);
}
int loopLight()
{
  int lightState = analogRead(light);
}
int loopButtons()
{
  int buttonsState = analogRead(buttons);
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
}
