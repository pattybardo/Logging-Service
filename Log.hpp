#ifndef LOG_H
#define LOG_H

#include <string>

class Log
{
  public:
    Log(std::string clientId, int logLevel, std::string message);

  private:
    std::string current_time;
    std::string clientId;
    int logLevel;
    std::string message;

};
#endif
