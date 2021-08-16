#include "LDRSensorHandler.h"
#include "../../../../BlynkManager.h"
#include "../../../Outgoing/OutgoingSender.h"

OutgoingSender LDRSensorHandler::handle(BlynkManager &bm, const utils::ostring *arguments, int length)
{
  OutgoingSender nullSender;
  if (length != 2)
    return nullSender;
  bm.writeVirtual(4, arguments[1].toInt());

  return nullSender;
}

LDRSensorHandler::~LDRSensorHandler() {}