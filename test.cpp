#include <fstream>
#include <iostream>
#include <string>

#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/lexical_cast.hpp>

//#include "catch2/catch.hpp"

#include "LoggingService.hpp"
#include "LoggingClient.hpp"

int main(){
  LoggingClient loggingClient;
  Request req;
  std::string line;

  std::ifstream myfile ("UnitTestExamples/logExample.txt");
  if (myfile.is_open()) {
    getline(myfile, line);
    req = loggingClient.receiveTextRequest(myfile, line);

    myfile.close();
  }
  std::cout << "Here" << '\n';

  return 0;
}
