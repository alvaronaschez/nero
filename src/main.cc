//#include "app.hh"
#include "editor.hh"
#include <vector>
#include <string>

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv, argv + argc};
  //return nero::run(args);
  return nero::run();
}
