// In a Catch project with multiple files, dedicate one file to compile the
// source code of Catch itself and reuse the resulting object file for linking.

// Let Catch provide main():
#define CATCH_CONFIG_MAIN

#include "catch2/catch.hpp"

/*
TEST_CASE( "1: All test cases reside in other .cpp files (empty)", "[multi-file:1]" )
{
}
*/
