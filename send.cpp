#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/lexical_cast.hpp>

#include "LoggingClient.hpp"

using namespace boost::interprocess;

int main (int argc, char** argv)
{
    try
    {
        message_queue mq
        (
           open_only,
           "mq"
        );

        LoggingClient loggingClient;

        if (argv[1]){
          //std::cout << argv[1] << '\n';
          std::string file = argv[1];
          std::string line;
          std::ifstream myfile (file);
          if (myfile.is_open())
          {
            while (getline (myfile,line)){
              // Run the reception of Request, and then sending the message
              Request me = loggingClient.receiveTextRequest(myfile, line);

              loggingClient.sendMessage(me, &mq);

              std::cout << "Message sent" << '\n';

            }
          } else {
            std::cout << "Unable to open file";
          }
        } else {
          while (true){

            Request me = loggingClient.receiveRequest();


            loggingClient.sendMessage(me, &mq);

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
