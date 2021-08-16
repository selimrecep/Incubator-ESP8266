#ifndef DHT11_INCOMING_H
#define DHT11_INCOMING_H
#include "../../IncomingHandler.h"
#include "../../../../BlynkManager.h"
#include "Utils/ostring.h"
class TempHumidHandler : public IncomingHandler
{
public:
  OutgoingSender handle(BlynkManager &bM, const utils::ostring *arguments, int length);
  ~TempHumidHandler();
};
#endif