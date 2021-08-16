#ifndef LDR_SENSOR_HANDLER_H
#define LDR_SENSOR_HANDLER_H
#include "../../IncomingHandler.h"
class LDRSensorHandler : public IncomingHandler
{
public:
  OutgoingSender handle(BlynkManager &bM, const utils::ostring *arguments, int length);
  ~LDRSensorHandler();
};
#endif