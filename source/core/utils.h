#pragma once

#include <string>
#include <filesystem>
#include <unordered_map>
#include <variant>
#include <optional>
#include <cstdint>

namespace core::utils
{

using error_type = bool;

struct StaticContent
{
  static error_type GetFile(const std::filesystem::path& path, std::string& data);
};

class DotEnv
{
  using value_type = std::variant<std::string, int32_t>;
public:
  static DotEnv& Instance();
  std::optional<value_type> GetValue(const std::string& key);

private:
  DotEnv();
  std::unordered_map<std::string, value_type> data_;
};

} // namespace core::utils

