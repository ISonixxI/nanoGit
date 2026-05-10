#include <iostream>
#include <sstream>
#include <string>

#include "commands/init.h"
#include "repository.h"

int main(int argc, char **argv) {

  if (argc < 2) {
    std::cerr << "usage: nanogit <command> [<args>]\n"
                 "\n"
                 "commands:\n"
                 "  init [path]    Create an empty nanogit repository\n";

    return 1;
  }

  std::string command = argv[1];

  if (command == "init") {
    nanogit::commands::init(argc - 2, argv + 2);
  } else {
    std::cerr << "unknown command : " << command << "\ntype nanogit -h to get help on using nanogit" << "\n";
    return 1;
  }

  return 0;
}