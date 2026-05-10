#pragma once
#include <filesystem>

namespace nanogit {

inline constexpr const char *repoDirName = ".nanogit";
int initialize_repository(const std::filesystem::path &current_path);

} // namespace nanogit