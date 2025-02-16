#pragma once

#include <string>
#include <filesystem>

namespace core
{

struct Utils
{
  using error = bool;

  static error GetStaticFile(const std::filesystem::path& path, std::string& data);
};

} // namespace core

