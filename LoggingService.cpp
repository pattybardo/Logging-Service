#include <string>
#include <iostream>

#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "LoggingService.hpp"

using namespace boost::interprocess;

// TODO: Unit test
Request LoggingService::receiveMessage(message_queue * mq)
{
    Request me;
    message_queue::size_type recvd_size;
    unsigned int priority;



    std::stringstream iss;
    std::string serialized_string;
    serialized_string.resize(MAX_SIZE);

    while (!mq->try_receive(&serialized_string[0], MAX_SIZE, recvd_size, priority)){
        usleep(0);
    }

    iss << serialized_string;

    boost::archive::text_iarchive ia(iss);
    ia >> me;
    return me;
}

// TODO: Unit test
void LoggingService::dumpLogs(Log * logs, int i, int logLevel, int bufferSize)
{
    // TODO: Deal with writing to to text file here
    for (int j=i; j < bufferSize+i; ++j){
        if (logs[j%bufferSize].getLogLevel() >= logLevel){
            std::cout << logs[j%bufferSize].getCurrentTime() << " "
                      << logs[j%bufferSize].getClientId() << " "
                      << logs[j%bufferSize].getLogLevelPrint()<< " : "
                      << logs[j%bufferSize].getMessage()
                      << '\n';
        }
    }
}

void LoggingService::clearLogs(Log * logs, int i, int bufferSize)
{
  std::cout << "Starting clear" << '\n';
  for (int j=i; j < bufferSize+i; ++j){
      logs[j%bufferSize].setLog();
  }
}
