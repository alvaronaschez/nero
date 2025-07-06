#include "commands.hh"

#include "util.hh"
#include "terminal.hh"
// commands

namespace nero {

Editor to_mode(Editor ed, Mode mode) {
  ed.mode = mode;
  return ed;
}

Editor to_normal_mode(Editor ed){
  return to_mode(ed, Mode::NORMAL);
}

Editor to_insert_mode(Editor ed){
  return to_mode(ed, Mode::INSERT);
}

Editor adjust_offset(Editor ed) {
  auto &off = ed.off;
  auto &cur = ed.cur;

  if (cur.y < off.y)
    off.y = cur.y;
  if (cur.x < off.x)
    off.x = cur.x;
  if (cur.y > off.y + ed.scr_size.y - 1)
    off.y = cur.y - (ed.scr_size.y - 1);
  if (cur.x > off.x + ed.scr_size.x - 1)
    off.x = cur.x - (ed.scr_size.x - 1);

  return ed;
}

Editor cursor_move(Editor ed, int dy, int dx) {
  auto max_y = ed.buf.text.size();
  if (max_y > 0)
    max_y -= 1;
  ed.cur.y =
      add_within_range(ed.cur.y, 0ul, max_y, static_cast<size_t>(std::abs(dy)),
                       dy >= 0 ? Sign::PLUS : Sign::MINUS);

  auto max_x = ed.buf.text[ed.cur.y]
                   .size(); // it is important to move up and down first, in
                            // order to accurately compute this value
  if (max_x > 0)
    max_x -= 1;
  ed.cur.x =
      add_within_range(ed.cur.x, 0ul, max_x, static_cast<size_t>(std::abs(dx)),
                       dx >= 0 ? Sign::PLUS : Sign::MINUS);

  return adjust_offset(ed);
}

Editor cursor_move_down(Editor ed){
  return cursor_move(ed, 1, 0);
}

Editor cursor_move_up(Editor ed){
  return cursor_move(ed, -1, 0);
}

Editor cursor_move_right(Editor ed){
  return cursor_move(ed, 0, 1);
}

Editor cursor_move_left(Editor ed){
  return cursor_move(ed, 0, -1);
}

Editor resize(Editor ed) {
  ed.scr_size = Terminal::size();
  return adjust_offset(ed);
}
} // namespace nero
