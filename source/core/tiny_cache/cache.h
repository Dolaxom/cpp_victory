#pragma once

#include <string>
#include <unordered_map>
#include <filesystem>

namespace core
{

class Cache
{
public:
  using status = bool;
  using result = std::pair<status, std::string>;

  result Get(const std::filesystem::path& key) const;
  status Add(const std::filesystem::path& key, const std::string& data);

private:
  // map<file_path, file_data>
  std::unordered_map<std::filesystem::path, std::string> cache_;
};

void InitCache(Cache& cache);

} // namespace core

