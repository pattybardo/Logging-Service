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
    REQUIRE( req.message == "This is a unit test message" );
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

/*
TEST_CASE( "3: Testing LoggingClient::clearRequest()", "[multi-file:2]" ) {
    LoggingClient loggingClient;
    Request req;

    std::ifstream myfile ("UnitTestExamples/dumpExample.txt");
    if (myfile.is_open()) {
      req = loggingClient.logTextRequest(myfile);

      myfile.close();
    }
    REQUIRE( req.action == 1);
    REQUIRE( req.logLevel == 2);
}
*/

TEST_CASE( "2: Unit Test compiling", "[multi-file:2]" ) {
    REQUIRE( 2 == 2 );
}
