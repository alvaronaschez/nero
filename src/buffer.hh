#pragma once

#include <string>

#include "common.hh"
// #include <utf8cpp/utf8.h>

namespace nero {
struct buffer {
  std::string file_name{""};
  nero::Text text;
};

buffer buffer_from_file(std::string file_name);
} // namespace nero
