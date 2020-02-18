#ifndef LOGGING_CLIENT_H
#define LOGGING_CLIENT_H

#include <fstream>

#include "Request.hpp"

class LoggingClient
{
  public:
    Request logRequest();
    Request logTextRequest(std::ifstream & myfile);

    Request dumpRequest();
    Request dumpTextRequest(std::ifstream & myfile);

    Request cleanRequest();

    Request receiveRequest();
    Request receiveTextRequest(std::ifstream & myfile, std::string line);

    void sendMessage(Request me, boost::interprocess::message_queue * mq);
};

#endif
