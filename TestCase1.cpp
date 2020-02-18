// 020-TestCase-1.cpp

// In a Catch project with multiple files, dedicate one file to compile the
// source code of Catch itself and reuse the resulting object file for linking.

// Let Catch provide main():
#define CATCH_CONFIG_MAIN

#include "catch2/catch.hpp"

TEST_CASE( "1: All test cases reside in other .cpp files (empty)", "[multi-file:1]" ) {
}

// ^^^
// Normally no TEST_CASEs in this file.
// Here just to show there are two source files via option --list-tests.

// Compile & run:
// - g++ -std=c++11 -Wall -c 020-TestCase-1.cpp
// - g++ -std=c++11 -Wall -o 020-TestCase 020-TestCase-1.o 020-TestCase-2.cpp
// g++ -std=c++17 -Wall TestCase1.cpp TestCase2.cpp -o TestCase
// ./TestCase --success
// g++ -std=c++17 -Wall
// ./020-TestCase --success

// Expected test case listing:
//
// prompt> 020-TestCase --list-tests *
// Matching test cases:
//   1: All test cases reside in other .cpp files (empty)
//       [multi-file:1]
//   2: Factorial of 0 is computed (fail)
//       [multi-file:2]
//   2: Factorials of 1 and higher are computed (pass)
//       [multi-file:2]
// 3 matching test cases
