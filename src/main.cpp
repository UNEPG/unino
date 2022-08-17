#include <Arduino.h>
#include <SoftwareSerial.h>
#include "SdsDustSensor.h"
#include <Adafruit_LPS2X.h>
#include <Wire.h>
#include "ClosedCube_HDC1080.h"

SdsDustSensor sds(10, 11); // passing HardwareSerial& as parameter RX/TX
// HDC1080
ClosedCube_HDC1080 hdc1080;
// Use LPS25 or LPS22 here
Adafruit_LPS25 lps;
Adafruit_Sensor *lps_temp, *lps_pressure;

void setup()
{
  // setup serial
  Serial.begin(9600);
  // setup sds011
  sds.begin(); // this line will begin Serial1 with given baud rate (9600 by default)
  // setup hdc1080
  hdc1080.begin(0x40);
  // Serial.print("Manufacturer ID=0x");
  // Serial.println(hdc1080.readManufacturerId(), HEX); // 0x5449 ID of Texas Instruments
  // Serial.print("Device ID=0x");
  // Serial.println(hdc1080.readDeviceId(), HEX); // 0x1050 ID of the device
}

void loop()
{
  sds.wakeup();
  // delay(30000); // working 30 seconds

  PmResult pm = sds.queryPm();
  if (pm.isOk())
  {
    // sds011
    Serial.print("PM2.5 = ");
    Serial.print(pm.pm25);
    Serial.print(", PM10 = ");
    Serial.println(pm.pm10);

    // hdc1080
    Serial.print("T=");
    Serial.print(hdc1080.readTemperature());
    Serial.print("C, RH=");
    Serial.print(hdc1080.readHumidity());
    Serial.println("%");

    // LPS2X
    if (lps.begin_I2C())
    {
      sensors_event_t pressure;
      sensors_event_t temp;
      lps_temp->getEvent(&temp);
      lps_pressure->getEvent(&pressure);
      Serial.println(pressure.pressure);
      Serial.println(temp.temperature);
    }
  }
  delay(3000);
}
