#include "DangerHandler.h"
#include "../../../../BlynkManager.h"
#include "../../../Outgoing/OutgoingSender.h"

OutgoingSender DangerHandler::handle(BlynkManager &bm, const utils::ostring *arguments, int length)
{
  OutgoingSender nullSender;
  if (length != 2)
    return nullSender;
  WidgetLED led(5);
  int dangerMode = arguments[1].toInt();
  if (dangerMode)
  {
    if (dangerMode == 2)
    {
      // Cold Injury
      bm.sendNotification("Dikkat! Makine SOĞUK!");
    }
    else
    {
      // Hot Injury
      bm.sendNotification("Dikkat! Makine SICAK!");
    }
    led.on();
  }
  else
    led.off();
  return nullSender;
}

DangerHandler::~DangerHandler() {}