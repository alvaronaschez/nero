#pragma once

#include <string>
#include "common.hh"

namespace nero {

class Terminal {
public:
  Terminal();
  ~Terminal();

  static void hide_cursor();
  static wint_t get_char();
  static void move(int y, int x);
  static void add(std::string);
  static void add(std::wstring);
  static void add(wint_t);
  static void refresh();
  static void clear();
  static Point size();
  
};

} // namespace nero
