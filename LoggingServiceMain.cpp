#include <string>
#include <iostream>
#include <fstream>

#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "LoggingService.hpp"

#define BUFFER_SIZE 5

using namespace boost::interprocess;

int main ()
{
    try
    {
        message_queue mq
        (
           open_or_create,
           "mq",
           100, //
           MAX_SIZE // This is the max size of a request. Defined in request.hpp
        );

        LoggingService loggingService;
        Log logs [BUFFER_SIZE];
        int i = 0;


        while (true){

            Request me = loggingService.receiveMessage(&mq);

            // Dev command for closing the service
            if (me.message == "exit()")
            {
                break;
            }

            // Log action
            if (me.action == 0) {
                logs[i%BUFFER_SIZE].setLog(me.clientId, me.logLevel, me.message);
                ++i;

            // Dump action
            } else if (me.action == 1) {
                std::cout << "Starting dump with log level: " << me.logLevel << '\n';
                loggingService.dumpLogs(logs, i, me.logLevel, BUFFER_SIZE);

            // Clear action
            } else {
                loggingService.clearLogs(logs,i, BUFFER_SIZE);
            }
        }

    }
    catch(interprocess_exception &ex)
    {
        std::cerr << ex.what() << '\n';
    }

    message_queue::remove("mq");
}
