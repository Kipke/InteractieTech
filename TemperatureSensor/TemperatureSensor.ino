#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 12
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress thermometer;

void setup(void)
{
  Serial.begin(9600);
  sensors.begin();
  if (!sensors.getAddress(thermometer, 0)) Serial.println("Unable to find address for Device 0"); 
  sensors.setResolution(thermometer, 9);
}

void loop(void)
{
  sensors.requestTemperatures();
  Serial.println(sensors.getTempC(thermometer));
  delay(200);
}
