#ifndef BLYNK_MANAGER_H
#define BLYNK_MANAGER_H
#include "BlynkSimpleEsp8266.h"
#include "Utils/ostring.h"
#include <string>

class BlynkManager
{
public:
  BlynkManager(const utils::ostring authToken, const utils::ostring serverDomain, unsigned const port);
  bool connect();
  void disconnect();
  bool run();
  bool isConnected();
  void writeVirtual(unsigned const virtualPin, float data);
  void sendTerminalData(utils::ostring data);
  void setEmergencyLedOff();
  void sendNotification(utils::ostring msg);

private:
  bool blynkHasConfigured = false;
  bool connected = false;
  void configureBlynk();
  utils::ostring authToken;
  utils::ostring serverDomain;
  unsigned const serverPort;
  WidgetTerminal terminal;
};
#endif
