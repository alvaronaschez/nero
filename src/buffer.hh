#pragma once

#include <string>

#include <immer/flex_vector.hpp>
// #include <utf8cpp/utf8.h>

namespace nero {

using line = immer::flex_vector<wchar_t>;
using text = immer::flex_vector<line>;

struct buffer {
  std::string file_name{""};
  nero::text text;
};

buffer buffer_from_file(std::string file_name);
} // namespace nero
