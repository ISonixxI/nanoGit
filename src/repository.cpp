#include "repository.h"
namespace nanogit {
int initialize_repository(std::filesystem::path &current_path) {
  /*
A subcommand called init that, when run in any directory, creates a .nanogit/ folder containing:

An objects/ subdirectory (empty for now — this is where blobs/trees/commits will live later)
A refs/heads/ subdirectory (empty — this is where branch pointers will live)
A HEAD file containing the text ref: refs/heads/main\n


Behavior requirements:

Running nanogit init in an empty directory creates the structure and prints a confirmation message with the absolute path.
Running nanogit init in a directory that already has a .nanogit/ folder should fail with an error message and a non-zero exit code. Don't clobber existing repos.
Running nanogit with no arguments should print a usage message.
Running nanogit somebogusword should print an error and the usage message.*/
  const std::filesystem::path repo_dir = current_path / repoDirName;

  if (std::filesystem::exists(repo_dir)) {
    std::cerr << repo_dir << " already exists not creating a new nanogit repository. " << std::endl;
    return 1;
  }

  std::error_code ec;

  std::filesystem::create_directories(repo_dir / "objects", ec);
  if (ec) {
    std::cerr << "Unexpected error in creating" << repo_dir / "objects" << " : \n"
              << ec.message() << std::endl;
    return 1;
  }

  std::filesystem::create_directories(repo_dir / "refs" / "head", ec);
  if (ec) {
    std::cerr << "Unexpected error in creating" << repo_dir / "refs" / "head" << " : \n"
              << ec.message() << std::endl;
    std::cerr << "deleting any files created by nanogit " << std::endl;
    std::filesystem::remove_all(repo_dir);
    return 1;
  }
  std::ofstream head(repo_dir / "HEAD");
  if (!head) {
    std::cerr << "failed to write HEAD" << std::endl;
    std::cerr << "deleting any files created by nanogit " << std::endl;
    std::filesystem::remove_all(repo_dir);
    return 1;
  }
  head << "ref: refs/heads/main\n";

  std::cout << "Initialized empty nanogit repository in "
            << std::filesystem::weakly_canonical(repo_dir).string() << std::endl;
  return 0;
}

} // namespace nanogit