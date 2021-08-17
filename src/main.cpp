#define BLYNK_SSL_USE_LETSENCRYPT

#include <Arduino.h>
#include "ESP8266Wifi.h"
#include <vector>
#include <SoftwareSerial.h>
#include "Network/WifiConnection.h"
#include "IoT/BlynkManager.h"
#include "IoT/Sensors/CommunicationManager.h"
//SoftwareSerial ardNanoSerial(3, 2);

WifiConnection wifi;
BlynkManager blynkManager{"passwordC", "domainname.com", 8080};
CommunicationManager comm(Serial, blynkManager);

void setup()
{

  // put your setup code here, to run once:
  Serial.begin(38400);
  //ardNanoSerial.begin(9600);
  wifi.addCredentials();
  pinMode(D5, OUTPUT);
  digitalWrite(D5, LOW);

  /*Serial.println(ESP.getFreeContStack());
  Serial.println(ESP.getFreeHeap());*/
  comm.init();
}

void loop()
{
  if (blynkManager.isConnected())
  {
    blynkManager.run();
  }
  else if (wifi.isConnected())
  {
    blynkManager.connect();
  }
  else
  {
    wifi.checkWifiAndConnect();
    delay(100);
  }
  /*
  if (ardNanoSerial.available())
  {
    sdm.addCharToQueue(ardNanoSerial.read());
  }*/

  if (Serial.available())
  {
    comm.addCharToQueue(Serial.read());
  }
}
