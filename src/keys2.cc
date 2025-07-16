#include <cassert>
#include <expected>
#include <iostream>
#include <optional>

unsigned char ctrl___(unsigned char c) {
  assert(c >= 64 && c <= 95 && "key cannot be converted to ctrl+key");
  return c & 0x1f;
}

unsigned char alt___(unsigned char c) {
  assert(c <= 127 && "key cannot be converted to alt+key");
  return c + 128;
}

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

std::expected<unsigned char, unsigned char> ctrl__(unsigned char c) {
  if (c < 64 || c > 95) {
      return std::unexpected(c);
  }
  return c & 0x1f;
}

std::expected<unsigned char, unsigned char> alt__(unsigned char c) {
  if (c > 127) {
    return std::unexpected(c);
  }
  return c + 128;
}

int main() {
  assert(alt___('c') == 227);
  assert(alt___('~') == 254);
  assert(ctrl___('C') == 3);

  assert(alt('c') == 227);
  assert(alt('~') == 254);
  assert(ctrl('C') == 3);
  assert(ctrl('a') == std::nullopt);

  assert(alt__('c').value() == 227);
  assert(alt__('~').value() == 254);
  assert(ctrl__('C').value() == 3);
  std::cout << "We did it!\n";
  assert(1 == 0 && "it fails here");
  return 0;
}
