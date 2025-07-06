#include <iostream>
#include <format>
extern "C"{
#define _XOPEN_SOURCE_EXTENDED 1 // sometimes needed for wchar support
#include <curses.h>
}

int main(){
  std::cout << "Hello World!\n";

  initscr();
  //cbreak();
  raw();
  noecho();
  noqiflush();
  keypad(stdscr, TRUE);
  set_escdelay(0); // recognize Esc quick
  nonl(); // distinguish between ctrl+j, ctrl+m and ENTER

  wint_t c;
  while(true){
    get_wch(&c);
    if(c == 'q') break;
    clear();
    if(c == 27){
        nodelay(stdscr, TRUE);

        int res = get_wch(&c);
        if(res != ERR){
            addstr(std::format("<alt-{}>", (char)c).c_str());
        } else {
            addstr("esc");
            // enter, tab, backspace, delete
        }
        nodelay(stdscr, FALSE);
        continue;
    }
    cchar_t cc;
    setcchar(&cc, (wchar_t*)&c, 0, 0, NULL);
    wadd_wch(stdscr, &cc);
    addstr(std::format("{}", c).c_str());
    if(c==KEY_BACKSPACE)
        addstr("bs");
    if(c==KEY_ENTER)
        addstr("enter");
    if(c==KEY_BTAB) addstr("btab");
    if(c==KEY_CTAB) addstr("ctab");
  }
  endwin();
  return 0;
}
