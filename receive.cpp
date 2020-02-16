#include <string>
#include <iostream>

#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "info.hpp"

#define MESSAGE_COUNT 100

using namespace boost::interprocess;



int main ()
{
    try
    {
        message_queue mq
            (
             open_only,
             "mq"
            );


        for (int i=0; i<MESSAGE_COUNT; ++i){
          message_queue::size_type recvd_size;
          unsigned int priority;

          info me;

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

          std::cout << me.id << " : " << me.name << std::endl;
        }

    }
    catch(interprocess_exception &ex)
    {
        std::cerr << ex.what() << std::endl;
    }

    message_queue::remove("mq");
}
