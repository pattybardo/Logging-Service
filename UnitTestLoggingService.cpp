#include <fstream>

#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/lexical_cast.hpp>

#include "catch2/catch.hpp"

//#include "LoggingService.hpp"
#include "LoggingClient.hpp"
#include "LoggingService.hpp"


TEST_CASE( "1: LoggingClient::logTextRequest()", "[multi-file:2]" ) {
    LoggingClient loggingClient;
    Request req;

    std::ifstream myfile ("UnitTestExamples/logExample.txt");
    if (myfile.is_open()) {
      req = loggingClient.logTextRequest(myfile);

      myfile.close();
    }
    REQUIRE( req.action == 0);
    REQUIRE( req.clientId == "Travis" );
    REQUIRE( req.logLevel == 1 );
    REQUIRE( req.message == "Test message" );
}

TEST_CASE( "2: Testing LoggingClient::dumpTextRequest()", "[multi-file:2]" ) {
    LoggingClient loggingClient;
    Request req;

    std::ifstream myfile ("UnitTestExamples/dumpExample.txt");
    if (myfile.is_open()) {
      req = loggingClient.dumpTextRequest(myfile);

      myfile.close();
    }
    REQUIRE( req.action == 1);
    REQUIRE( req.logLevel == 2);
}

TEST_CASE( "3: Testing LoggingClient::clearRequest()", "[multi-file:2]" ) {
    LoggingClient loggingClient;
    Request req;

    req = loggingClient.clearRequest();

    REQUIRE( req.action == 2);
}

TEST_CASE( "4: Testing LoggingClient::receiveTextRequest()", "[multi-file:2]" ) {
  LoggingClient loggingClient;
  Request req;
  std::string line;

  std::ifstream myfile ("UnitTestExamples/requestExample.txt");
  if (myfile.is_open()) {
    getline(myfile, line);
    req = loggingClient.receiveTextRequest(myfile, line);

    myfile.close();
  }
  REQUIRE( req.action == 0);
  REQUIRE( req.clientId == "Nathan" );
  REQUIRE( req.logLevel == 2 );
  REQUIRE( req.message == "North rocks!" );
}

TEST_CASE( "5: Testing LoggingClient::sendMessage() with  LoggingService::receiveMessage()", "[multi-file:2]" ) {
  LoggingClient loggingClient;
  LoggingService loggingService;
  Request req(0, "Edwin", 1, "Test message");
  std::string line;

  boost::interprocess::message_queue mq_test
  (
    boost::interprocess::open_or_create,
    "mq_test",
    10,
    MAX_SIZE
  );

  loggingClient.sendMessage(req, &mq_test);
  Request recvReq = loggingService.receiveMessage(&mq_test);
  boost::interprocess::message_queue::remove("mq_test");

  REQUIRE( recvReq.action == 0);
  REQUIRE( recvReq.clientId == "Edwin" );
  REQUIRE( recvReq.logLevel == 1 );
  REQUIRE( recvReq.message == "Test message" );

}

TEST_CASE( "6: Testing Log::setLog()", "[multi-file:2]" ) {
    Log log;
    log.setLog("Alex", 1, "South");

    REQUIRE( log.getClientId() == "Alex" );
    REQUIRE( log.getLogLevel() == 1 );
    REQUIRE( log.getMessage() == "South" );
}

TEST_CASE( "7: Testing LoggingService::clearLogs()", "[multi-file:2]" ) {
  LoggingService loggingService;
  Log logs [2];
  logs[0].setLog("Patrick", 0, "0");
  logs[1].setLog("Patrick", 1, "1");

  loggingService.clearLogs(logs, 0, 2);
  REQUIRE( logs[0].getClientId() == "" );
  REQUIRE( logs[1].getClientId() == "" );
  REQUIRE( logs[0].getLogLevel() == -1 );
  REQUIRE( logs[1].getLogLevel() == -1 );
  REQUIRE( logs[0].getMessage() == "" );
  REQUIRE( logs[1].getMessage() == "" );
}
