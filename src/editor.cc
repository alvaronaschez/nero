#include "editor.hh"
#include "buffer.hh"
#include "terminal.hh"
#include <immer/flex_vector_transient.hpp>

namespace nero {
editor_view view(editor editor) {
  // immer::flex_vector_transient<line> txt = editor.buffer.text.transient();
  // txt.drop(editor.offset.y);
  // txt.take(editor.screen_size.y);
  // return {.text = txt.persistent()};

  text txt =
      editor.buffer.text.drop(editor.offset.y).take(editor.screen_size.y);
  immer::flex_vector_transient<line> result{};
  for (auto row : txt) {
    result.push_back(row.drop(editor.offset.x).take(editor.screen_size.x));
  }
  return {
      .text = result.persistent(),
      .cursor = {editor.cursor.y-editor.offset.y, editor.cursor.x-editor.offset.x},
  };
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

void draw(editor editor) {
  render(view(editor));
}

int run() {
  Terminal t{};
  editor editor{};
  editor.screen_size = Terminal::size();
  editor.buffer = buffer_from_file("src/editor.cc");
  while (true) {
    draw(editor);
    wint_t ch = Terminal::get_char();
    if (ch == 'q')
      break;
    switch (ch) {
    case 'h':
      editor = move_left(editor);
      break;
    case 'j':
      editor = move_down(editor);
      break;
    case 'k':
      editor = move_up(editor);
      break;
    case 'l':
      editor = move_right(editor);
      break;
    }
  }
  return 0;
}

// commands

editor move_up(editor editor, size_t dy) {
  auto& y = editor.cursor.y;
  auto& off = editor.offset.y;

  y = y > dy ? y - dy : 0;
  if(y<off)
    off = y;

  return editor;
}

editor move_down(editor editor, size_t dy) {

  auto& y = editor.cursor.y;
  auto& off = editor.offset.y;
  const auto& screen_height = editor.screen_size.y;
  const auto buffer_len = editor.buffer.text.size();

  y = std::min(y+dy, buffer_len-1);
  if(y>off+screen_height-1){
    off = y - screen_height + 1;
  }

  return editor;
}

editor move_left(editor editor, size_t dx) {
  if (editor.cursor.x >= dx)
    editor.cursor.x--;
  return editor;
}

editor move_right(editor editor, size_t dx) {
  size_t buffer_row = editor.cursor.y + editor.offset.y +dx -dx;
  size_t line_len = editor.buffer.text[buffer_row].size();
  if (editor.cursor.x < std::min(line_len - 1, editor.screen_size.x - 1))
    editor.cursor.x++;
  else if (editor.cursor.x == editor.screen_size.x - 1 &&
           editor.offset.x < line_len - 1)
    editor.offset.x++;
  return editor;
}

} // namespace nero
