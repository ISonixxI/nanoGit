#include <functional>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include <openssl/sha.h>
#include <zlib.h>

#include "commands/init.h"
#include "repository.h"

int main(int argc, char **argv) {

  if (argc < 2) {
    std::cerr << "usage: nanogit <command> [<args>]\n"
                 "\n"
                 "commands:\n"
                 "  init [path]    Create an empty nanogit repository\n";

    return 0;
  }

  std::filesystem::path path = std::filesystem::current_path();
  std::string command = argv[1];

  if (command == "init") {
    nanogit::commands::init(argc - 2, argv + 2);
  } else {
    std::cerr << "unknown command : " << command << "\ntype nanogit -h to get help on using nanogit" << std::endl;
  }

  return 0;
}