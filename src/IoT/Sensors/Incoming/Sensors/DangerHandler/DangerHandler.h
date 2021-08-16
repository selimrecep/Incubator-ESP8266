#ifndef DANGER_HANDLER_H
#define DANGER_HANDLER_H
#include "../../IncomingHandler.h"
class DangerHandler : public IncomingHandler
{
public:
  OutgoingSender handle(BlynkManager &bM, const utils::ostring *arguments, int length);
  ~DangerHandler();
};
#endif