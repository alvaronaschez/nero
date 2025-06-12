//#define unit_test
#ifdef unit_test

#include "util.hh"
#include <cassert>
#include <iostream>

int main() {
  using namespace nero;
  std::cout << add_within_range(5u, 0u, 10u, 6u, Sign::MINUS) << std::endl;
  std::cout << add_within_range(5u, 0u, 10u, 6u, Sign::PLUS) << std::endl;
  assert(0u == add_within_range(5u, 0u, 10u, 6u, Sign::MINUS));
  assert(10u == add_within_range(5u, 0u, 10u, 6u, Sign::PLUS));
  return 0;
}

#endif
