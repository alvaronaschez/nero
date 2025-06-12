#pragma once

#include "common.hh"
#include "buffer.hh"

#include <immer/flex_vector.hpp>

namespace nero {

struct editor {
  point cursor{};
  point offset{};
  point screen_size{};
  nero::buffer buffer{};
};

//using line = immer::flex_vector<wchar_t>;
//using text = immer::flex_vector<line>;
struct editor_view {
  nero::text text; // from buffer.hh, put it in a separate file with point
  point cursor;
};

void render(editor_view);
editor_view view(editor);
void draw(editor, editor);

void load_file(editor, std::string file_name);
  

editor move_left(editor, size_t = 1);
editor move_down(editor, size_t = 1);
editor move_up(editor, size_t = 1);
editor move_right(editor, size_t = 1);

int run();
} // namespace nero
