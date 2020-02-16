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
             open_or_create,
             "mq",
             100,
             MAX_SIZE
            );

        std::string message;

        while (true){
          getline(std::cin, message);

          if (message == ""){
            break;
          }

          info me(getpid(), message);

          std::stringstream oss;

          boost::archive::text_oarchive oa(oss);
          oa << me;

          std::string serialized_string(oss.str());
          mq.send(serialized_string.data(), serialized_string.size(), 0);
          //std::cout << me.id << " : " << me.name << std::endl;
        }




        std::cout << "Here" << '\n';
    }
    catch(interprocess_exception &ex)
    {
        std::cerr << ex.what() << std::endl;
    }
}
