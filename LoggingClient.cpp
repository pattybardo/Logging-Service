#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/lexical_cast.hpp>

#include "LoggingClient.hpp"


Request LoggingClient::logRequest()
{

  unsigned int action = 0;
  std::string clientId;
  std::string logLevel;
  std::string message;

  std::cout << "Client ID: " << '\n';
  getline(std::cin, clientId);

  std::cout << "Log level (0,1,2 - info, warning, error): " << '\n';
  getline(std::cin, logLevel);

  std::cout << "Message: " << '\n';
  getline(std::cin, message);

  Request req(action, clientId, boost::lexical_cast<int>(logLevel), message);

  return req;

}

Request LoggingClient::logTextRequest(std::ifstream & myfile)
{

  unsigned int action = 0;
  std::string clientId;
  std::string logLevel;
  std::string message;

  getline(myfile, clientId);
  getline(myfile, logLevel);
  getline(myfile, message);

  Request req(action, clientId, boost::lexical_cast<int>(logLevel), message);

  return req;

}

Request LoggingClient::dumpRequest()
{
  unsigned int action = 1;
  std::string clientId;
  //string becuase getLine does not accept integers, cast back later
  std::string dumpLevel;
  std::string message;



  std::cout << "Select the minimum dump level (0,1,2 - info, warning, error): " << '\n';
  getline(std::cin, dumpLevel);

  Request req(action, clientId, boost::lexical_cast<int>(dumpLevel), message);

  return req;

}

Request LoggingClient::dumpTextRequest(std::ifstream & myfile)
{
  unsigned int action = 1;
  std::string clientId;
  std::string dumpLevel;
  std::string message;

  getline(myfile, dumpLevel);

  Request req(action, clientId, boost::lexical_cast<int>(dumpLevel), message);

  return req;

}

Request LoggingClient::clearRequest()
{
  unsigned int action = 2;
  std::string clientId;
  int logLevel;
  std::string message;

  Request req(action, clientId, logLevel, message);

  return req;
}

Request LoggingClient::receiveRequest()
{

  std::string request;
  std::cout << "Choose 0, 1, 2 (log, dump, clean) \n";
  getline(std::cin, request);
  int x = boost::lexical_cast<int>(request);
  //std::cin >> x;

  // TODO: maybe do something about this
  if (x == 0){
    return LoggingClient::logRequest();
  } else if (x == 1){
    return LoggingClient::dumpRequest();
  } else {
    return LoggingClient::clearRequest();
  }


}

Request LoggingClient::receiveTextRequest(std::ifstream & myfile, std::string line)
{
  unsigned int action = boost::lexical_cast<int>(line);
  if (action == 0){
    return LoggingClient::logTextRequest(myfile);
  } else if (action == 1){
    return LoggingClient::dumpTextRequest(myfile);
  } else {
    return LoggingClient::clearRequest();
  }
}


void LoggingClient::sendMessage(Request me, boost::interprocess::message_queue * mq)
{
  std::stringstream oss;
  boost::archive::text_oarchive oa(oss);
  oa << me;

  std::string serialized_string(oss.str());
  while(!mq->try_send(serialized_string.data(), serialized_string.size(), 0)){
    usleep(0);
  }
}
