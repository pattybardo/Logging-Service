#include <string>
#include <iostream>


#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "info.hpp"
#include "Log.hpp"

#define MESSAGE_COUNT 20

using namespace boost::interprocess;


// TODO
/*
void dump(info logs[])
{
  for (int i=0; i < std::size(logs); ++i){
    std::cout << logs[i].clientId << " : " << logs[i].message << '\n';
  }
}
*/

int main ()
{
    try
    {

        message_queue mq
        (
           open_or_create,
           "mq",
           100,
           MAX_SIZE
        );

        info me;
        Log logs [MESSAGE_COUNT];

        for (int i=0; i<MESSAGE_COUNT; ++i){
          message_queue::size_type recvd_size;
          unsigned int priority;



          std::stringstream iss;
          std::string serialized_string;
          serialized_string.resize(MAX_SIZE);

          while (!mq.try_receive(&serialized_string[0], MAX_SIZE, recvd_size, priority)){
            usleep(0);
          }

          //mq.try_receive(&serialized_string[0], MAX_SIZE, recvd_size, priority);
          iss << serialized_string;

          boost::archive::text_iarchive ia(iss);
          ia >> me;

          if (me.message == "exit()")
          {
            break;
          }
          //TODO
          std::cout << "Test action value: " << me.action << '\n';
          if (me.action == 1) {
            std::cout << "Starting dump" << '\n';
            --i;
            //TODO: make a seperate function
            for (int j=0; j < std::size(logs); ++j){
              if (logs[j].getLogLevel() >= 0){
                  std::cout << logs[j].getCurrentTime()
                  << logs[j].getLogLevel()<< " : "
                  << logs[j].getMessage()
                  <<std::endl;
              }

            }
          } else {
            //std::cout << "receiving log: " << me.message << '\n';
            logs[i].setLog(me.clientId, me.logLevel, me.message);
            // TODO: Change the storage of all the messages to a buffer of messages
            // This buffer will hold all of the logs, and mayb as well design it to be
            // circular from the beginning
            //std::cout << me[i].clientId << " : " << me[i].message << std::endl;
          }





        }

    }
    catch(interprocess_exception &ex)
    {
        std::cerr << ex.what() << std::endl;
    }

    message_queue::remove("mq");
}
