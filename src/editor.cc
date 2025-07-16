#include "editor.hh"
#include "buffer.hh"
#include "commands.hh"
#include "common.hh"
#include "keys.hh"
#include "terminal.hh"

#include <immer/flex_vector_transient.hpp>
#include <immer/map.hpp>
#include <string>

namespace nero {

EditorView view(Editor ed) {
  Text txt = ed.buf.text.drop(ed.off.y).take(ed.scr_size.y);
  immer::flex_vector_transient<Line> result{};
  for (auto row : txt) {
    result.push_back(row.drop(ed.off.x).take(ed.scr_size.x));
  }
  return {.text = result.persistent(),
          .cursor = {ed.cur.y - ed.off.y, ed.cur.x - ed.off.x}};
}

void render(EditorView view) {
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

void draw(Editor ed) { render(view(ed)); }

constexpr std::array<Command, 256> get_normal_map() {
  std::array<Command, 256> res{nullptr};

  using us = unsigned short;

  res[(us)K::h] = cursor_move_left;
  res[(us)K::j] = cursor_move_down;
  res[(us)K::k] = cursor_move_up;
  res[(us)K::l] = cursor_move_right;

  res[(us)K::esc] = to_insert_mode;

  return res;
}

int run() {
  Terminal t{};
  Editor ed{};
  ed.scr_size = Terminal::size();
  ed.buf = buffer_from_file("src/editor.cc");

  auto normal_map = get_normal_map();

  while (true) {
    draw(ed);
    Keystroke ks = Terminal::get_char();
    if (ks.k) {
      K k = *ks.k;
      if (k == K::q)
        break;
      auto cmd = normal_map[(unsigned char)k];
      if (cmd != nullptr)
        ed = cmd(ed);

    } else {
      if (ks.keycode == 0632)
        ed = resize(ed);
    }
  }
  return 0;
}

} // namespace nero
