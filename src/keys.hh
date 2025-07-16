#pragma once

#include <cwchar>
#include <optional>

namespace nero {
enum struct K : unsigned char {
  // asci begin
  ctrl_at, // ^@
  ctrl_A,  // ^A
  ctrl_B,
  ctrl_C,
  ctrl_D,
  ctrl_E,
  ctrl_F,
  ctrl_G,
  ctrl_H, // backspace
  tab,    // ^I and  \t
  ctrl_J, // line feed
  ctrl_K,
  ctrl_L,
  enter, // ^M and enter
  ctrl_N,
  ctrl_O,
  ctrl_P,
  ctrl_Q,
  ctrl_R,
  ctrl_S,
  ctrl_T,
  ctrl_U,
  ctrl_V,
  ctrl_W,
  ctrl_X,
  ctrl_Y,
  ctrl_Z,
  esc, // ^[ and esc
  ctrl_backslash,
  ctrl_right_bracket,
  ctrl_caret,
  ctrl_underscore,
  space,             //  \s
  exclamation,       //  !
  double_quote,      //  "
  hash,              //  #
  dollar,            //  $
  percent,           //  %
  ampersand,         //  &
  single_quote,      //  '
  left_parentheses,  //  (
  right_parentheses, //  )
  star,              //  *
  plus,              //  +
  comma,             //  ,
  minus,             //  -
  dot,               //  .
  slash,             //  /
  _0,
  _1,
  _2,
  _3,
  _4,
  _5,
  _6,
  _7,
  _8,
  _9,
  colon,         //  :
  semicolon,     //  ;
  less_than,     //  <
  equal,         //  =
  greater_than,  //  >
  interrogation, //  ?
  at,            //  @
  A,
  B,
  C,
  D,
  E,
  F,
  G,
  H,
  I,
  J,
  K,
  L,
  M,
  N,
  O,
  P,
  Q,
  R,
  S,
  T,
  U,
  V,
  W,
  X,
  Y,
  Z,
  left_bracket,  // [
  backslash,     // \ //
  right_bracket, // ]
  caret,         //  ^
  underscore,    //  _
  backtick,      // `
  a,
  b,
  c,
  d,
  e,
  f,
  g,
  h,
  i,
  j,
  k,
  l,
  m,
  n,
  o,
  p,
  q,
  r,
  s,
  t,
  u,
  v,
  w,
  x,
  y,
  z,
  left_brace,  // {
  pipe,        // |
  right_brace, // }
  tilde,       //  ~
  del,
  // ascii end
  // alt begin
  alt_ctrl_at, // ^@
  alt_ctrl_A,  // ^A
  alt_ctrl_B,
  alt_ctrl_C,
  alt_ctrl_D,
  alt_ctrl_E,
  alt_ctrl_F,
  alt_ctrl_G,
  alt_ctrl_H, // backspace
  alt_tab,    // ^I and  \t
  alt_ctrl_J, // line feed
  alt_ctrl_K,
  alt_ctrl_L,
  alt_enter, // ^M and enter
  alt_ctrl_N,
  alt_ctrl_O,
  alt_ctrl_P,
  alt_ctrl_Q,
  alt_ctrl_R,
  alt_ctrl_S,
  alt_ctrl_T,
  alt_ctrl_U,
  alt_ctrl_V,
  alt_ctrl_W,
  alt_ctrl_X,
  alt_ctrl_Y,
  alt_ctrl_Z,
  alt_esc, // ^[ and esc
  alt_ctrl_backslash,
  alt_ctrl_right_bracket,
  alt_ctrl_caret,
  alt_ctrl_underscore,
  alt_space,             //  \s
  alt_exclamation,       //  !
  alt_double_quote,      //  "
  alt_hash,              //  #
  alt_dollar,            //  $
  alt_percent,           //  %
  alt_ampersand,         //  &
  alt_single_quote,      //  '
  alt_left_parentheses,  //  (
  alt_right_parentheses, //  )
  alt_star,              //  *
  alt_plus,              //  +
  alt_comma,             //  ,
  alt_minus,             //  -
  alt_dot,               //  .
  alt_slash,             //  /
  alt__0,
  alt__1,
  alt__2,
  alt__3,
  alt__4,
  alt__5,
  alt__6,
  alt__7,
  alt__8,
  alt__9,
  alt_colon,         //  :
  alt_semicolon,     //  ;
  alt_less_than,     //  <
  alt_equal,         //  =
  alt_greater_than,  //  >
  alt_interrogation, //  ?
  alt_at,            //  @
  alt_A,
  alt_B,
  alt_C,
  alt_D,
  alt_E,
  alt_F,
  alt_G,
  alt_H,
  alt_I,
  alt_J,
  alt_K,
  alt_L,
  alt_M,
  alt_N,
  alt_O,
  alt_P,
  alt_Q,
  alt_R,
  alt_S,
  alt_T,
  alt_U,
  alt_V,
  alt_W,
  alt_X,
  alt_Y,
  alt_Z,
  alt_left_bracket,  // [
  alt_backslash,     // \ //
  alt_right_bracket, // ]
  alt_caret,         //  ^
  alt_underscore,    //  _
  alt_backtick,      // `
  alt_a,
  alt_b,
  alt_c,
  alt_d,
  alt_e,
  alt_f,
  alt_g,
  alt_h,
  alt_i,
  alt_j,
  alt_k,
  alt_l,
  alt_m,
  alt_n,
  alt_o,
  alt_p,
  alt_q,
  alt_r,
  alt_s,
  alt_t,
  alt_u,
  alt_v,
  alt_w,
  alt_x,
  alt_y,
  alt_z,
  alt_left_brace,  // {
  alt_pipe,        // |
  alt_right_brace, // }
  alt_tilde,       //  ~
  // alt end
};

struct Keystroke {
  wint_t keycode;
  std::optional<K> k;
};

} // namespace nero
