#pragma once

#include "buffer.hh"
#include "common.hh"

#include <immer/flex_vector.hpp>

namespace nero {

struct editor {
  point cur{};
  point off{};
  point scr_size{};
  nero::buffer buf{};
};

// using line = immer::flex_vector<wchar_t>;
// using text = immer::flex_vector<line>;
struct editor_view {
  nero::text text; // from buffer.hh, put it in a separate file with point
  point cursor;
};

void render(editor_view);
editor_view view(editor);
void draw(editor, editor);

void load_file(editor, std::string file_name);

editor cursor_move(editor, int dy, int dx);
editor resize(editor);

int run();
} // namespace nero
