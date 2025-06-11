#include "hi.hh"
#include "terminal.hh"

#include <iostream>
#include <optional>
#include <string>
#include <variant>

#include <immer/flex_vector.hpp>
#include <immer/vector.hpp>

#include <lager/event_loop/manual.hpp>
#include <lager/store.hpp>
#include <lager/util.hpp>

extern "C" {
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
}

namespace nero {

// model
struct model {
  int value = 0;
};

// actions
struct increment_action {};
struct decrement_action {};
struct reset_action {
  int new_value = 0;
};
using action = std::variant<increment_action, decrement_action, reset_action>;

// reducer
model update(model c, action action) {
  return std::visit(lager::visitor{
                        [&](increment_action) {
                          ++c.value;
                          return c;
                        },
                        [&](decrement_action) {
                          --c.value;
                          return c;
                        },
                        [&](reset_action a) {
                          c.value = a.new_value;
                          return c;
                        },
                    },
                    action);
}

// intent
std::optional<action> intent(char event) {
  switch (event) {
  case '+':
    return increment_action{};
  case '-':
    return decrement_action{};
  case '.':
    return reset_action{};
  default:
    return std::nullopt;
  }
}

// draw
struct ui_description{std::string s;};

ui_description view(model curr) {
  return {std::to_string(curr.value)};
}

void render(ui_description view){
  Terminal::clear(); 
  Terminal::move(0,0);
  Terminal::add(view.s);
  Terminal::refresh();
}

void draw(model curr) {
  render(view(curr));
}

int run() {

  // this project
  say_hi();

  // immer
  const auto v0 = immer::vector<int>{};
  const auto v1 = v0.push_back(13);
  assert(v0.size() == 0 && v1.size() == 1 && v1[0] == 13);

  const auto v2 = v1.set(0, 42);
  assert(v1[0] == 13 && v2[0] == 42);

  // lua
  lua_State *L = luaL_newstate();
  double v = lua_version(L);
  std::cout << "lua version: " << v << std::endl;
  lua_close(L);

  // lager + ncurses
  auto store =
      lager::make_store<action>(model{}, lager::with_manual_event_loop{});
  watch(store, draw);

  Terminal terminal{};

  auto event = char{};
  store.dispatch(reset_action{7});
  while (true) {
    event = terminal.get_char();
    if (event == 'q')
      break;
    if (auto act = intent(event))
      store.dispatch(*act);
  }

  return 0;
}

} // namespace nero

int main() { return nero::run(); }
