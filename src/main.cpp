/*
_    _       _ _   _
| |  | |     (_) \ | |
| |  | |_ __  _|  \| | ___
| |  | | '_ \| | . ` |/ _ \
| |__| | | | | | |\  | (_) |
 \____/|_| |_|_|_| \_|\___/

An example of feeding data into the PSoTT protocol.
Used Devices:
  - Arduino Uno
  - SDS011
  - HDC1080
  - LPS22 (Can be also LPS25)
 */

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "SdsDustSensor.h"
#include <Wire.h>
#include "ClosedCube_HDC1080.h"
#include "ClosedCube_LPS25HB.h"

// PSoTT Definitions
String DEVID = "devID=unino";
String RETURN = "\r\n";

SdsDustSensor sds(10, 11); // passing HardwareSerial& as parameter RX/TX
// HDC1080
ClosedCube_HDC1080 hdc1080;
// Use LPS25 or LPS22 here
ClosedCube_LPS25HB lps25hb;

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
  lps25hb.begin(0x5C);
}

void loop()
{
  // PSoTT Start
  Serial.print(RETURN);
  Serial.print(DEVID);
  Serial.print(RETURN);
  // sds wakeup
  sds.wakeup();
  PmResult pm = sds.queryPm();
  if (pm.isOk())
  {
    Serial.print("subID=air");
    Serial.print(RETURN);
    // sds011
    Serial.print("pm25=");
    Serial.print(pm.pm25);
    Serial.print(RETURN);
    Serial.print("pm10=");
    Serial.print(pm.pm10);
    Serial.print(RETURN);
  }
  Serial.print("subID=meteo");
  Serial.print(RETURN);
  // hdc1080
  Serial.print("temperature=");
  Serial.print(hdc1080.readTemperature());
  Serial.print(RETURN);
  Serial.print("humidity=");
  Serial.print(hdc1080.readHumidity());
  Serial.print(RETURN);

  // LPS2X
  Serial.print("pressure=");
  Serial.print(lps25hb.readPressure());
  Serial.print(RETURN);
  // PSoTT End
  Serial.print(RETURN);
  delay(3000);
}
