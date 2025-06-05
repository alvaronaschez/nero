#pragma once

#include <string>

namespace nero {

class Terminal {
public:
  Terminal();
  ~Terminal();

  static char get_char();
  static void move(int y, int x);
  static void add(std::string);
  static void refresh();
  static void clear();
};

} // namespace nero
