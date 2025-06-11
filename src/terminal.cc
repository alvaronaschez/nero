#include "terminal.hh"

#include "ncurses.hh"
#include <string>

namespace nero {
Terminal::Terminal() {
  ncurses::initscr();
  ncurses ::cbreak();
  ncurses ::noecho();
  ncurses ::intrflush(ncurses::stdscr, FALSE);
  ncurses ::keypad(ncurses::stdscr, TRUE);

  ncurses::curs_set(0); // hide cursor
}

Terminal::~Terminal() {
  ncurses::clear();
  ncurses::endwin();
}

void Terminal::move(int y, int x) { ncurses::move(y, x); }

void Terminal::add(std::string s) {
  ncurses::waddstr(ncurses::stdscr, s.c_str());
}

void Terminal::add(std::wstring s){
  ncurses::waddwstr(ncurses::stdscr, s.c_str());
}

void Terminal::add(wint_t wc){
  //ncurses::waddwstr(ncurses::stdscr, s.c_str());
  wchar_t wstr[2] = { static_cast<wchar_t>(wc), L'\0' };
  ncurses::waddwstr(ncurses::stdscr, wstr);
}

void Terminal::refresh() { ncurses::refresh(); }

void Terminal::clear() { ncurses::clear(); }

wint_t Terminal::get_char() { 
  wint_t c;
  ncurses::wget_wch(ncurses::stdscr, &c);
  return c;
  //return ncurses::wgetch(ncurses::stdscr); 
}
} // namespace nero
