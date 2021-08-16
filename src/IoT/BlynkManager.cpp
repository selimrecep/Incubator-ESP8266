#include "Arduino.h"
#include "BlynkManager.h"
#include "BlynkSimpleEsp8266.h"
#include "GlobalVars.h"
#include "Utils/ostring.h"

BlynkWifi Blynk(_blynkTransport);
BlynkManager::BlynkManager(const utils::ostring authToken, const utils::ostring domain, unsigned const port) : serverPort(port), terminal(V8)
{
  this->authToken = authToken;
  this->serverDomain = domain;
};

void BlynkManager::configureBlynk()
{
  Blynk.config(authToken.c_str(), serverDomain.c_str(), serverPort);
}

bool BlynkManager::connect()
{
  if (!blynkHasConfigured)
  {
    configureBlynk();
    blynkHasConfigured = true;
  }
  connected = Blynk.connect();
  if (connected)
  {
    setEmergencyLedOff();
  }
  //Serial.println(connected);
  return connected;
}
void BlynkManager::setEmergencyLedOff()
{
  writeVirtual(5, 0);
}

void BlynkManager::disconnect()
{
  Blynk.disconnect();
  connected = false;
}

bool BlynkManager::run()
{
  connected = Blynk.run();
  return connected;
}

bool BlynkManager::isConnected()
{
  // Oh yeah sweating
  return connected == true;
}

void BlynkManager::writeVirtual(unsigned const virtualPin, float data)
{
  Blynk.virtualWrite(virtualPin, data);
}

void BlynkManager::sendTerminalData(utils::ostring data)
{
  terminal.print(data.c_str());
  terminal.flush();
}

void BlynkManager::sendNotification(utils::ostring msg)
{
  Blynk.notify(msg.c_str());
}

/***** HANDLERS ****/
BLYNK_WRITE(V3)
{
  bool switchOff = param.asInt();
  if (switchOff)
  {
    OutgoingSender switchFuseOffSender{"danger|1", 10};
    switchFuseOffSender.serializeAndSend(comm.getStream());
  }
}
BLYNK_WRITE(V7)
{
  const char *text = param.asString();

  comm.getStream()->print(text);
  comm.getStream()->print('\0');
} /*
BLYNK_WRITE(V8)
{
  const char *text = param.asString();
  for (size_t i = 0; i < param.getLength(); i++)
    comm.addCharToQueue(text[i]);
  comm.addCharToQueue('\0');
}*/

BLYNK_WRITE(V9)
{
  double val = param.asDouble();
  comm.calibrateTemperature(val);
}
BLYNK_WRITE(V10)
{
  double val = param.asDouble();
  comm.calibrateHumidity(val);
}