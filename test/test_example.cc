
#define CATCH_CONFIG_MAIN

#include <catch2/catch_test_macros.hpp> // Catch3 v3

#include "src/hi.hh"

#include <iostream>
#include <sstream>

TEST_CASE("Example test", "[example]") {
  REQUIRE(1 + 1 == 2);

  std::stringstream buffer;
  std::streambuf *oldCountStreamBuf = std::cout.rdbuf();
  std::cout.rdbuf(buffer.rdbuf());

  nero::say_hi();

  std::cout.rdbuf(oldCountStreamBuf);

  std::string output = buffer.str();
  REQUIRE(output == "Hello World!\n");
}
