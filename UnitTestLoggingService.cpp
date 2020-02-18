#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "catch2/catch.hpp"

#include "LoggingService.hpp"
#include "LoggingClient.hpp"


TEST_CASE( "1: Testing Request construction", "[multi-file:2]" ) {
    REQUIRE( 2 == 2 );
}

TEST_CASE( "2: Unit Test compiling", "[multi-file:2]" ) {
    REQUIRE( 2 == 2 );
}
