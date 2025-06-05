#include "terminal.hh"

#include "ncurses.hh"

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

void Terminal::refresh() { ncurses::refresh(); }

void Terminal::clear() { ncurses::clear(); }

char Terminal::get_char() { return ncurses::wgetch(ncurses::stdscr); }

} // namespace nero
