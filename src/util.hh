#pragma once

#include <algorithm>
#include <type_traits>

namespace nero {

enum Sign { PLUS, MINUS };

template <typename T>
  requires std::is_integral_v<T> && std::is_unsigned_v<T>
inline T add_within_range(T v, T m, T M, T dv, Sign dv_sign = Sign::PLUS) {
  switch (dv_sign) {
  case Sign::PLUS:
    return std::min(std::max(m, v + dv), M);
  case Sign::MINUS:
    return std::min(v + m > dv ? v - dv : m, M);
  default:
    __builtin_unreachable();
  }
}
} // namespace nero
