#include "app.hh"

#include "terminal.hh"

#include <iostream>
#include <string>
#include <variant>

#include <immer/flex_vector.hpp>

#include <lager/event_loop/manual.hpp>
#include <lager/store.hpp>
#include <lager/util.hpp>

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
  wint_t c;
};

model update(model, app_action);
// using key_result = std::pair<model, lager::effect<app_action>>;
using key_result = model;

// key_reducer
key_result update(model m, key_action e) {
  app_action new_action;
  switch (e.c) {
  case '+':
  case 0403: // key up
    new_action = increment_action{};
    break;
  case '-':
  case 0402: // key down
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
// std::optional<app_action> intent(wint_t event) {
//  switch (event) {
//  case '+':
//  case 0403: // key up
//    return increment_action{};
//  case '-':
//  case 0402: // key down
//    return decrement_action{};
//  case '.':
//    return reset_action{};
//  default:
//    return std::nullopt;
//  }
//}

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

int run(std::vector<std::string> argv) {
  if (argv.size() != 2) {
    std::cout << "Incorrect number of arguments" << std::endl;
    return 1;
  }
  std::string file_name = argv[1];
  std::cout << file_name << std::endl;

  auto store =
      lager::make_store<key_action>(model{}, lager::with_manual_event_loop{});
  watch(store, draw);

  Terminal terminal{};

  wint_t event;
  // store.dispatch(reset_action{7});
  store.dispatch(key_action{'.'});
  while (true) {
    event = Terminal::get_char();
    if (event == 'q')
      break;
    store.dispatch(key_action{event});
  }

  return 0;
}
} // namespace nero
