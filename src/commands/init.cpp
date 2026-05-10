#include "init.h"
#include "repository.h"

namespace nanogit::commands {
int init(int argc, char **argv) {
  std::filesystem::path repo_root = ".";

  if (argc > 1) {
    std::cerr << "usage: nanogit init [path]\n";
    return 1;
  }

  if (argc == 1) {
    repo_root = argv[0];
  }

  return initialize_repository(repo_root);
}
} // namespace nanogit::commands
