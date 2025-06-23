#pragma once

#include <string>
#include <filesystem>

namespace core::utils
{

struct StaticContent
{
  using error = bool;

  static error GetFile(const std::filesystem::path& path, std::string& data);
};

} // namespace core::utils

