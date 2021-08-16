#include "DataHandlers.h"
#include "Incoming/Sensors/TempHumidHandler/TempHumidHandler.h"
#include "Incoming/Sensors/LDRSensorHandler/LDRSensorHandler.h"
#include "Incoming/Sensors/DangerHandler/DangerHandler.h"
DataHandlers::DataHandlers()
{
  initializeHandlers();
}
void DataHandlers::initializeHandlers()
{
  registerHandler(IncomingHandler_t::TempHumidHandler_t, new TempHumidHandler());
  registerHandler(IncomingHandler_t::LDRHandler_t, new LDRSensorHandler());
  registerHandler(IncomingHandler_t::DangerHandler_t, new DangerHandler());
}

void DataHandlers::registerHandler(IncomingHandler_t handlerType, IncomingHandler *handler)
{
  handlers[handlerType] = handler;
}

IncomingHandler *DataHandlers::getHandler(IncomingHandler_t handlerType)
{
  return handlers[handlerType];
}

DataHandlers::~DataHandlers()
{
  for (int i = 0; i < handlerCount; i++)
  {
    delete handlers[i];
  }
}