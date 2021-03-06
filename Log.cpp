#include <chrono>
#include <ctime>
#include <iostream>

#include "Log.hpp"

Log::Log()
{
  setLog();
}

// TODO: Unit test
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

// TODO: Unit test
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


// TODO: Unit test
std::string Log::getLogLevelPrint()
{
  if (logLevel == 0){
    return "[info]";
  } else if (logLevel == 1) {
    return "[warning]";
  } else if (logLevel == 2) {
    return "[error]";
  } else {
    return "[-------default value, should not be showing up------]";
  }
}

std::string Log::getMessage()
{
  return message;
}
