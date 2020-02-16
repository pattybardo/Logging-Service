#include "Log.hpp"
#include <chrono>
#include <ctime>

Log::Log(std::string clientId, int logLevel, std::string message)
{
  time_t rawtime;
  struct tm * timeinfo;
  char buffer[80];

  time (&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfo);
  std::string str(buffer);

  current_time = str;

  clientId = clientId;
  logLevel = logLevel;
  message = message;
}
