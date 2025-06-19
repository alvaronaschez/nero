#pragma once

#include "buffer.hh"
#include "common.hh"

#include <immer/flex_vector.hpp>

namespace nero {

enum Mode {
  NORMAL,
  INSERT,
};

struct Editor {
  Mode mode{Mode::NORMAL};
  Point cur{};
  Point off{};
  Point scr_size{};
  nero::buffer buf{};
};

// using line = immer::flex_vector<wchar_t>;
// using text = immer::flex_vector<line>;
struct EditorView {
  nero::Text text; // from buffer.hh, put it in a separate file with point
  Point cursor;
};

void render(EditorView);
EditorView view(Editor);
void draw(Editor, Editor);

void load_file(Editor, std::string file_name);

Editor cursor_move(Editor, int dy, int dx);
Editor resize(Editor);

int run();
} // namespace nero
