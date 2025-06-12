#pragma once

#include <immer/flex_vector.hpp>

namespace nero {

struct point {
  size_t y{0};
  size_t x{0};
};


using line = immer::flex_vector<wchar_t>;
using text = immer::flex_vector<line>;
}
