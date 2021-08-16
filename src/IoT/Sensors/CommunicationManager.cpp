#include "CommunicationManager.h"
#include "../BlynkManager.h"
#include <sstream>
#include <vector>
#include <string>
#include "Utils/ostring.h"
#include "EEPROM.h"
#include "Incoming/Sensors/TempHumidHandler/TempHumidHandler.h"

int countOccurences(char *charArr, int length, char delim);

CommunicationManager::CommunicationManager(Stream &serial, BlynkManager &blynkManager) : packetHandlers{}, lastCommand{(unsigned long)32}, serial(serial), blynkManager(blynkManager)
{
}

void CommunicationManager::init()
{
  EEPROM.begin(2 * sizeof(double));
  EEPROM.get(0, humidityAdd);
  EEPROM.get(0 + sizeof(double), temperatureAdd);
}
void CommunicationManager::incomingData(utils::ostring lastCommand)
{
  int argumentCount; /*
  Serial.print("> ");
  Serial.println(lastCommand.c_str());
  Serial.print(lastCommand.capacity());
  Serial.print("_");
  Serial.println(lastCommand.length());*/
  const utils::ostring *arguments = lastCommand.createSplit('|', argumentCount);
  if (argumentCount < 2)
  {
    delete[] arguments;
    return;
  }
  /* Handling incoming packets */
  //Serial.println(arguments[0].c_str());
  /*
  Serial.println("a");
  Serial.println(arguments[0].c_str());*/
  IncomingHandler_t handlerType = NullHandler_t;
  if ((arguments[0] == "temp" || arguments[0] == "humid") && blynkManager.isConnected())
  {
    //Serial.println("dht11 data got.");
    handlerType = IncomingHandler_t::TempHumidHandler_t;
  }
  else if (arguments[0] == "ldr")
  {
    handlerType = IncomingHandler_t::LDRHandler_t;
  }
  else if (arguments[0] == "inDanger")
  {
    handlerType = IncomingHandler_t::DangerHandler_t;
  }
  if (handlerType != IncomingHandler_t::NullHandler_t)
  {
    OutgoingSender responseSender = packetHandlers.getHandler(handlerType)->handle(blynkManager, arguments, argumentCount);

    if (!responseSender.isNull())
    {
      responseSender.serializeAndSend(&serial);
    }
  }

  delete[] arguments;
}
void CommunicationManager::calibrateHumidity(double val)
{
  OutgoingSender calibHumidSender{"calibrate|0"};
  calibHumidSender.addFloat(val);
  calibHumidSender.serializeAndSend(getStream());
  humidityAdd = val;
  EEPROM.put(0, val);
  EEPROM.commit();
}
void CommunicationManager::calibrateTemperature(double val)
{
  OutgoingSender calibHumidSender{"calibrate|1"};
  calibHumidSender.addFloat(val);
  calibHumidSender.serializeAndSend(getStream());
  temperatureAdd = val;
  EEPROM.put(0 + sizeof(double), val);
  EEPROM.commit();
}
Stream *CommunicationManager::getStream()
{
  return &serial;
}
void CommunicationManager::addCharToQueue(char ch)
{
  if (ch == '\0' || ch == '\r' || ch == '\n' || commandLength >= 31)
  {
    if (commandLength >= 1)
    {
      if (lockDown)
      {
        lockDown = false;
        commandLength = 0;
        return;
      }
      utils::ostring a{};
      a += (int)commandLength;
      lastCommand.changeStrLengthUnsafe(commandLength);
      blynkManager.sendTerminalData("esp> ");
      blynkManager.sendTerminalData(a + " => ");
      blynkManager.sendTerminalData(lastCommand);
      blynkManager.sendTerminalData("\r\n");

      //Serial.print(" >");
      //Serial.println(lastCommand.c_str());
      commandLength = 0;
      incomingData(lastCommand);
    }
  }
  else if (lockDown == false)
  {
    if (commandLength == 0 && ch == 'q')
    {
      lockDown = true;
      return;
    }
    lastCommand[commandLength++] = ch;
  }
  else
  {
    commandLength++;
  }
}

int countOccurences(char *charArr, int length, char delim)
{
  int i = 0;
  int n = 0;
  for (i = 0; i < length; i++)
  {
    if (charArr[i] == delim)
      n++;
  }
  return n;
}