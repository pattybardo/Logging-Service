#ifndef LOG_H
#define LOG_H

#include <string>

class Log
{
  public:
    Log();
    void setLog(std::string clientId, int logLevel, std::string message);
    void setLog();

    std::string getCurrentTime();
    std::string getClientId();
    int getLogLevel();
    std::string getMessage();


  private:
    std::string currentTime;
    std::string clientId;
    int logLevel;
    std::string message;

};
#endif
