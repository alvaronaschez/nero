#include "buffer.hh"

#include <fstream>
#include <immer/flex_vector.hpp>
#include <immer/flex_vector_transient.hpp>
#include <locale>
#include <string>

namespace nero {
buffer buffer_from_file(std::string file_name) {
  std::wifstream file{file_name};

  if (!file) // TODO: error control
    return {};

  file.imbue(std::locale("en_US.UTF-8"));

  immer::flex_vector_transient<immer::flex_vector<wchar_t>> text{};

  std::wstring line;
  while (std::getline(file, line)) {
    immer::flex_vector_transient<wchar_t> buffer_line{};
    for (wchar_t ch : line) {
      buffer_line.push_back(ch);
    }
    text.push_back(buffer_line.persistent());
  }

  return {.file_name = file_name, .text = text.persistent()};
}
} // namespace nero
