#include "hi.hh"
#include "terminal.hh"

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
// app actions
struct increment_action {};
struct decrement_action {};
struct reset_action {
  int new_value = 0;
};
using app_action =
    std::variant<increment_action, decrement_action, reset_action>;

// key actions
struct key_action {
  char c;
};

model update(model, app_action);
// using key_result = std::pair<model, lager::effect<app_action>>;
using key_result = model;

// key_reducer
key_result update(model m, key_action e) {
  app_action new_action;
  switch (e.c) {
  case '+':
    new_action = increment_action{};
    break;
  case '-':
    new_action = decrement_action{};
    break;
  case '.':
    new_action = reset_action{};
    break;
  default:
    return m;
  };

  return update(m, new_action);
}

// reducer
model update(model c, app_action action) {
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
std::optional<app_action> intent(char event) {
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
struct ui_description {
  std::string s;
};

ui_description view(model curr) { return {std::to_string(curr.value)}; }

void render(ui_description view) {
  Terminal::clear();
  Terminal::move(0, 0);
  Terminal::add(view.s);
  Terminal::refresh();
}

void draw(model curr) { render(view(curr)); }

int run() {
  auto store =
      lager::make_store<app_action>(model{}, lager::with_manual_event_loop{});
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
