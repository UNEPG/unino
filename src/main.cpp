#include <Arduino.h>
#include <SoftwareSerial.h>
#include "SdsDustSensor.h"
SdsDustSensor sds(10, 11); // passing HardwareSerial& as parameter RX/TX

void setup()
{
  Serial.begin(9600);
  sds.begin(); // this line will begin Serial1 with given baud rate (9600 by default)
}

void loop()
{
  sds.wakeup();
  // delay(30000); // working 30 seconds

  PmResult pm = sds.queryPm();
  if (pm.isOk())
  {
    Serial.print("PM2.5 = ");
    Serial.print(pm.pm25);
    Serial.print(", PM10 = ");
    Serial.println(pm.pm10);
  }
  else
  // has some problem with the sensor
  {
    Serial.print("Could not read values from sensor, reason: ");
    Serial.println(pm.statusToString());
  }
  delay(1000);
}