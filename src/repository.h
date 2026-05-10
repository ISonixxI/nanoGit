#pragma once
#include <filesystem>
#include <fstream>
#include <iostream>
namespace nanogit {

inline constexpr const char *repoDirName = ".nanogit";
int initialize_repository(std::filesystem::path &current_path);

} // namespace nanogit