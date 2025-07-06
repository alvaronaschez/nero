#pragma once

#include "editor.hh"
#include <functional>

namespace nero {
using Command = std::function<Editor(Editor)>;

Editor to_normal_mode(Editor ed);
Editor to_insert_mode(Editor ed);

Editor cursor_move_left(Editor ed);
Editor cursor_move_right(Editor ed);
Editor cursor_move_up(Editor ed);
Editor cursor_move_down(Editor ed);

Editor resize(Editor ed);

} // namespace nero

