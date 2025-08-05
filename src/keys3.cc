#include <cassert>
#include <iostream>
#include <optional>

std::optional<unsigned char> ctrl(unsigned char c) {
  if (c < 64 || c > 95) {
    return std::nullopt;
  }
  return c & 0x1f;
}

std::optional<unsigned char> alt(unsigned char c) {
  if (c > 127) {
    return std::nullopt;
  }
  return c + 128;
}

int main() {
  assert(alt('c') == 227);
  assert(alt('~') == 254);
  assert(ctrl('C') == 3);
  assert(ctrl('a') == std::nullopt);

  std::cout << "We did it!\n";
  assert(1 == 0 && "it fails here");
  return 0;
}
