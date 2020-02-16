#include <string>
#include <sstream>
#include <iostream>

#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/archive/text_oarchive.hpp>

#include "info.hpp"

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

        std::string message;

        while (true){
          getline(std::cin, message);
          if (message == ""){
            break;
          }

          info me(0,std::to_string(getpid()), 0, message);

          std::stringstream oss;
          boost::archive::text_oarchive oa(oss);
          oa << me;

          std::string serialized_string(oss.str());
          while(!mq.try_send(serialized_string.data(), serialized_string.size(), 0)){
            usleep(0);
          }
          std::cout << "Message sent" << '\n';
          //std::cout << me.id << " : " << me.name << std::endl;
        }

    }
    catch(interprocess_exception &ex)
    {
        std::cerr << ex.what() << std::endl;
    }
}
