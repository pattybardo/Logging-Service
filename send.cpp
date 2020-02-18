#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/lexical_cast.hpp>

#include "info.hpp"

using namespace boost::interprocess;


// TODO: Unit test
info logInfo() {

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

  info rInfo(action, clientId, boost::lexical_cast<int>(logLevel), message);

  return rInfo;

}

// TODO: Unit test
info logTextInfo(std::ifstream & myfile) {

  unsigned int action = 0;
  std::string clientId;
  std::string logLevel;
  std::string message;

  getline(myfile, clientId);
  getline(myfile, logLevel);
  getline(myfile, message);

  info rInfo(action, clientId, boost::lexical_cast<int>(logLevel), message);

  return rInfo;

}

// TODO: Unit test
info dumpInfo() {
  unsigned int action = 1;
  std::string clientId;
  //string becuase getLine does not accept integers, cast back later
  std::string dumpLevel;
  std::string message;



  std::cout << "Select the minimum dump level (0,1,2 - info, warning, error): " << '\n';
  getline(std::cin, dumpLevel);

  info rInfo(action, clientId, boost::lexical_cast<int>(dumpLevel), message);

  return rInfo;

}

info dumpTextInfo(std::ifstream & myfile) {
  unsigned int action = 1;
  std::string clientId;
  std::string dumpLevel;
  std::string message;

  getline(myfile, dumpLevel);

  std::cout << dumpLevel << '\n';
  info rInfo(action, clientId, boost::lexical_cast<int>(dumpLevel), message);

  return rInfo;

}

// TODO: Unit test
info cleanInfo() {
  unsigned int action = 2;
  std::string clientId;
  int logLevel;
  std::string message;

  info rInfo(action, clientId, logLevel, message);

  return rInfo;
}

// TODO: Unit test
info receiveInfo(){

  std::string request;
  std::cout << "Choose 0, 1, 2 (log, dump, clean) \n";
  getline(std::cin, request);
  int x = boost::lexical_cast<int>(request);
  //std::cin >> x;

  // TODO: maybe do something about this
  if (x == 0){
    return logInfo();
  } else if (x == 1){
    return dumpInfo();
  } else {
    return cleanInfo();
  }


}

info receiveTextInfo(std::ifstream & myfile, std::string line)
{
  unsigned int action = boost::lexical_cast<int>(line);
  if (action == 0){
    return logTextInfo(myfile);
  } else if (action == 1){
    return dumpTextInfo(myfile);
  } else {
    return cleanInfo();
  }
}


// TODO: Unit test
void sendMessage(info me, message_queue * mq)
{
  std::stringstream oss;
  boost::archive::text_oarchive oa(oss);
  oa << me;

  std::string serialized_string(oss.str());
  while(!mq->try_send(serialized_string.data(), serialized_string.size(), 0)){
    usleep(0);
  }
}


int main (int argc, char** argv)
{
    try
    {
        message_queue mq
        (
           open_only,
           "mq"
        );

        if (argv[1]){
          //std::cout << argv[1] << '\n';
          std::string file = argv[1];
          std::string line;
          std::ifstream myfile (file);
          if (myfile.is_open())
          {
            while (getline (myfile,line)){
              // Run the reception of info, and then sending the message
              info me = receiveTextInfo(myfile, line);

              sendMessage(me, &mq);

              std::cout << "Message sent" << '\n';

            }
          } else {
            std::cout << "Unable to open file";
          }
        } else {
          while (true){

            info me = receiveInfo();


            sendMessage(me, &mq);

            std::cout << "Message sent" << '\n';

            // This is here for testing, just to terminate the receive service
            if (me.message == "exit()"){
              break;
            }
            //std::cout << me.id << " : " << me.name << std::endl;
          }
        }



    }
    catch(interprocess_exception &ex)
    {
        std::cerr << ex.what() << '\n';
    }
}
