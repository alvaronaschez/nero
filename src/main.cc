#include "hi.hh"

#include <iostream>

#include <immer/flex_vector.hpp>
#include <immer/vector.hpp>

extern "C" {
#include <ncurses.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

int main() {
  // this project
  say_hi();

  // immer
  const auto v0 = immer::vector<int>{};
  const auto v1 = v0.push_back(13);
  assert(v0.size() == 0 && v1.size() == 1 && v1[0] == 13);

  const auto v2 = v1.set(0, 42);
  assert(v1[0] == 13 && v2[0] == 42);

  // lua
  lua_State *L = luaL_newstate();
  double v = lua_version(L);
  std::cout << "lua version: " << v << std::endl;
  lua_close(L);

  // curses
  initscr();
  cbreak();
  noecho();
  intrflush(stdscr, FALSE);
  keypad(stdscr, TRUE);

  addstr("Hola Curses!");
  getch();

  clear();
  endwin();

  return 0;
}
