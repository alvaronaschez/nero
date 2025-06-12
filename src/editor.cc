#include "editor.hh"
#include "buffer.hh"
#include "common.hh"
#include "terminal.hh"
#include "util.hh"
#include <immer/flex_vector_transient.hpp>

namespace nero {
editor_view view(editor ed) {
  text txt = ed.buf.text.drop(ed.off.y).take(ed.scr_size.y);
  immer::flex_vector_transient<line> result{};
  for (auto row : txt) {
    result.push_back(row.drop(ed.off.x).take(ed.scr_size.x));
  }
  return {.text = result.persistent(),
          .cursor = {ed.cur.y - ed.off.y, ed.cur.x - ed.off.x}};
}

void render(editor_view view) {
  Terminal::clear();
  Terminal::move(0, 0);

  int i = 0;
  for (auto row : view.text) {
    for (auto ch : row) {
      Terminal::add(ch);
    }
    Terminal::move(++i, 0);
  }
  Terminal::move(view.cursor.y, view.cursor.x);
  Terminal::refresh();
}

void draw(editor ed) { render(view(ed)); }

// commands

editor adjust_offset(editor ed) {
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

editor cursor_move(editor ed, int dy, int dx) {
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

editor resize(editor ed) {
  ed.scr_size = Terminal::size();
  return adjust_offset(ed);
}

int run() {
  Terminal t{};
  editor ed{};
  ed.scr_size = Terminal::size();
  ed.buf = buffer_from_file("src/editor.cc");
  while (true) {
    draw(ed);
    wint_t ch = Terminal::get_char();
    if (ch == 'q')
      break;
    switch (ch) {
    case 'h':
      ed = cursor_move(ed, 0, -1);
      break;
    case 'j':
      // ed = cursor_move_down(ed);
      ed = cursor_move(ed, 1, 0);
      break;
    case 'k':
      ed = cursor_move(ed, -1, 0);
      break;
    case 'l':
      ed = cursor_move(ed, 0, 1);
      break;
    case 0632:
      ed = resize(ed);
      break;
    }
  }
  return 0;
}
} // namespace nero
