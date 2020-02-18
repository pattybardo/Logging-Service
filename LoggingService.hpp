#ifndef LOGGING_SERVICE_H
#define LOGGING_SERVICE_H

#include "Request.hpp"
#include "Log.hpp"

class LoggingService
{
  public:
    Request receiveMessage(boost::interprocess::message_queue * mq);
    void dumpLogs(Log * logs, int i, int logLevel);
    void clearLogs(Log * logs, int i);
};
#endif
