#pragma once

#include <immer/flex_vector.hpp>

namespace nero {

struct Point {
  size_t y{0};
  size_t x{0};
};


using Line = immer::flex_vector<wchar_t>;
using Text = immer::flex_vector<Line>;
}
