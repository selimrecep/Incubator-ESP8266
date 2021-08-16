#ifndef DATA_HANDLERS_H
#define DATA_HANDLERS_H
#include "Incoming/IncomingHandler.h"

constexpr unsigned MAX_HANDLER_COUNT = 3;

enum IncomingHandler_t
{
  NullHandler_t = -1,
  TempHumidHandler_t = 0,
  LDRHandler_t,
  DangerHandler_t
};

class DataHandlers
{
public:
  DataHandlers();
  ~DataHandlers();
  IncomingHandler *getHandler(IncomingHandler_t handlerType);

private:
  int handlerCount = 0;
  IncomingHandler *handlers[MAX_HANDLER_COUNT];
  void initializeHandlers();
  void registerHandler(IncomingHandler_t handlerType, IncomingHandler *handler);
};
#endif