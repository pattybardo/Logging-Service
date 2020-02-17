#include "Log.hpp"
#include <chrono>
#include <ctime>
#include <iostream>

// TODO
Log::Log()
{
  setLog();
}

void Log::setLog(std::string pClientId, int pLogLevel, std::string pMessage)
{
  time_t rawtime;
  struct tm * timeinfo;
  char buffer[80];

  time (&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(buffer,sizeof(buffer),"[%d-%m-%Y %H:%M:%S]",timeinfo);
  std::string str(buffer);


  currentTime = str;
  //std::cout << "setLog: " << currentTime << '\n';

  clientId = pClientId;
  logLevel = pLogLevel;
  message = pMessage;
}

void Log::setLog()
{
  currentTime = "";
  clientId = "";
  logLevel = -1;
  message = "";

}

std::string Log::getCurrentTime()
{
  return currentTime;
}

std::string Log::getClientId()
{
  return clientId;
}

int Log::getLogLevel()
{
  return logLevel;
}

std::string Log::getMessage()
{
  return message;
}


/*
std::ostream& operator<< (std::ostream &out, Log const &log) {
    out << "[" << log.getCurrentTime() << "] ";

    out << log.getClientId() << " ";
    out << log.getLogLevel() << " ";
    out << log.getMessage() << ";";

    return out;
}
*/
