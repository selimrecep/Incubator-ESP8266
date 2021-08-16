#include "Arduino.h"
#include "TempHumidHandler.h"
#include "../../../../BlynkManager.h"
#include "Utils/ostring.h"
#include "GlobalVars.h"
OutgoingSender TempHumidHandler::handle(BlynkManager &bM, const utils::ostring *arguments, int length)
{
  OutgoingSender nullSender;
  if (length != 2)
    return nullSender;

  OutgoingSender sender("oksir");
  sender.addString("done");
  float val;

  val = arguments[1].toFloat();
  //Serial.print("Hey temp: ");
  //Serial.println(temperature);
  if (arguments[0] == "temp")
    bM.writeVirtual(1, val + comm.temperatureAdd);
  else
    bM.writeVirtual(2, val + comm.humidityAdd);
  return sender;
}

TempHumidHandler::~TempHumidHandler() {}