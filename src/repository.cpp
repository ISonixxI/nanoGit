#include <fstream>
#include <iostream>

#include "repository.h"
namespace nanogit {
int initialize_repository(std::filesystem::path &current_path) {

  const std::filesystem::path repo_dir = current_path / repoDirName;

  if (std::filesystem::exists(repo_dir)) {
    std::cerr << repo_dir.string() << " already exists not creating a new nanogit repository. \n";
    return 1;
  }

  std::error_code ec;

  std::filesystem::create_directories(repo_dir / "objects", ec);
  if (ec) {
    std::cerr << "Unexpected error in creating" << repo_dir / "objects" << " : \n"
              << ec.message() << "\n";
    return 1;
  }

  std::filesystem::create_directories(repo_dir / "refs" / "heads", ec);
  if (ec) {
    std::cerr << "Unexpected error in creating" << repo_dir / "refs" / "heads" << " : \n"
              << ec.message() << "\n";
    std::cerr << "deleting any files created by nanogit " << "\n";
    std::filesystem::remove_all(repo_dir);
    return 1;
  }
  std::ofstream head(repo_dir / "HEAD");
  if (!head) {
    std::cerr << "failed to write HEAD" << "\n";
    std::cerr << "deleting any files created by nanogit " << "\n";
    std::filesystem::remove_all(repo_dir);
    return 1;
  }
  head << "ref: refs/heads/main\n";

  std::cout << "Initialized empty nanogit repository in "
            << std::filesystem::weakly_canonical(repo_dir).string() << "\n";
  return 0;
}

} // namespace nanogit