#include "terminal.hh"

#include "ncurses.hh"
#include <ncurses.h>
#include <string>

namespace nero {
Terminal::Terminal() {
  ncurses::initscr();
  // ncurses ::cbreak();
  ncurses::raw();
  ncurses ::noecho();
  ncurses::noqiflush();
  ncurses ::keypad(ncurses::stdscr, TRUE);
  ncurses::set_escdelay(0); // recognize Esc quick
  ncurses::nonl();          // distinguish between ctrl+j, ctrl+m and Enter
}

Terminal::~Terminal() {
  ncurses::clear();
  ncurses::endwin();
}

void Terminal::hide_cursor() { ncurses::curs_set(0); }

void Terminal::move(int y, int x) { ncurses::move(y, x); }

void Terminal::add(std::string s) {
  ncurses::waddstr(ncurses::stdscr, s.c_str());
}

void Terminal::add(std::wstring s) {
  ncurses::waddwstr(ncurses::stdscr, s.c_str());
}

void Terminal::add(wint_t wc) {
  // ncurses::waddwstr(ncurses::stdscr, s.c_str());
  wchar_t wstr[2] = {static_cast<wchar_t>(wc), L'\0'};
  ncurses::waddwstr(ncurses::stdscr, wstr);
}

void Terminal::refresh() { ncurses::refresh(); }

void Terminal::clear() { ncurses::clear(); }

Keystroke Terminal::get_char() {
  wint_t c;
  ncurses::wget_wch(ncurses::stdscr, &c);

  // check if Alt+whatever combo
  if (c == 27) {
    ncurses::nodelay(ncurses::stdscr, TRUE);

    int res = ncurses::wget_wch(ncurses::stdscr, &c);
    ncurses::nodelay(ncurses::stdscr, FALSE);
    if (res != ERR) {
      if (c < 128){
        return {.keycode=c, .k=static_cast<K>(c + 128)};
      }
    } else {
      return {.keycode=c, .k=K::esc};
    }
  }

  // not alt combo
  if (c < 128)
    return {.keycode=c, .k=static_cast<K>(c)};

  return {.keycode=c, .k=std::nullopt};
}

Point Terminal::size() {
  Point p;
  p.x = getmaxx(ncurses::stdscr);
  p.y = getmaxy(ncurses::stdscr);
  return p;
}

} // namespace nero
