#include <fstream>

#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/lexical_cast.hpp>

#include "catch2/catch.hpp"

//#include "LoggingService.hpp"
#include "LoggingClient.hpp"


TEST_CASE( "1: LoggingClient::logTextRequest()", "[multi-file:2]" ) {
    LoggingClient loggingClient;
    Request req;

    std::ifstream myfile ("UnitTestExamples/logExample.txt");
    if (myfile.is_open()) {
      req = loggingClient.logTextRequest(myfile);

      myfile.close();
    }
    REQUIRE( req.action == 0);
    REQUIRE( req.clientId == "Test" );
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
  REQUIRE( req.clientId == "Tester" );
  REQUIRE( req.logLevel == 2 );
  REQUIRE( req.message == "North rocks!" );
}


TEST_CASE( "2: Unit Test compiling", "[multi-file:2]" ) {
    REQUIRE( 2 == 2 );
}
