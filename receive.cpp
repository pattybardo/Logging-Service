#include <string>
#include <iostream>


#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "info.hpp"
#include "Log.hpp"

#define BUFFER_SIZE 5

using namespace boost::interprocess;


// TODO: Unit test
info receiveMessage(message_queue * mq)
{
    info me;
    message_queue::size_type recvd_size;
    unsigned int priority;



    std::stringstream iss;
    std::string serialized_string;
    serialized_string.resize(MAX_SIZE);

    while (!mq->try_receive(&serialized_string[0], MAX_SIZE, recvd_size, priority)){
        usleep(0);
    }

    //mq.try_receive(&serialized_string[0], MAX_SIZE, recvd_size, priority);
    iss << serialized_string;

    boost::archive::text_iarchive ia(iss);
    ia >> me;
    return me;
}

// TODO: Unit test
void dumpLogs(Log * logs, int i, int logLevel)
{
    // TODO: Deal with writing to to text file here
    for (int j=i; j < BUFFER_SIZE+i; ++j){
        if (logs[j%BUFFER_SIZE].getLogLevel() >= logLevel){
            std::cout << logs[j%BUFFER_SIZE].getCurrentTime() << " "
                      << logs[j%BUFFER_SIZE].getClientId() << " "
                      << logs[j%BUFFER_SIZE].getLogLevelPrint()<< " : "
                      << logs[j%BUFFER_SIZE].getMessage()
                      << '\n';
        }

    }
}

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


        Log logs [BUFFER_SIZE];
        int i = 0;

        while (true){

            info me = receiveMessage(&mq);

            // Dev command for closing the service
            if (me.message == "exit()")
            {
                break;
            }

            //TODO
            std::cout << "Test action value: " << me.action << '\n';

            // Log action
            if (me.action == 0) {
                //
                logs[i%BUFFER_SIZE].setLog(me.clientId, me.logLevel, me.message);
                ++i;

            // Dump action
            } else if (me.action == 1) {
                std::cout << "Starting dump" << '\n';
                //TODO: make a seperate function
                dumpLogs(logs, i, me.logLevel);
                /*
                for (int j=i; j < std::size(logs)+i; ++j){
                    if (logs[j%BUFFER_SIZE].getLogLevel() >= me.logLevel){
                        std::cout << logs[j%BUFFER_SIZE].getCurrentTime() << " "
                                  << logs[j%BUFFER_SIZE].getClientId() << " "
                                  << logs[j%BUFFER_SIZE].getLogLevelPrint()<< " : "
                                  << logs[j%BUFFER_SIZE].getMessage()
                                  << '\n';
                    }

                }
                */

            // Clear action
            } else {
                std::cout << "Starting clear" << '\n';
                for (int j=i; j < std::size(logs)+i; ++j){
                    logs[j%BUFFER_SIZE].setLog();
                }
            }





        }

    }
    catch(interprocess_exception &ex)
    {
        std::cerr << ex.what() << '\n';
    }

    message_queue::remove("mq");
}
