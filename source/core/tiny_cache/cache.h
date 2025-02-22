#pragma once

#include <string>
#include <unordered_map>
#include <filesystem>

namespace core
{

class Cache
{
public:
  Cache() = default;

  using status = bool;
  using result = std::pair<status, std::string>;

  result Get(const std::string& key) const;
  status Add(const std::string& key, const std::string& data);

private:
  // map<file_path, file_data>
  // NOTE: We can't use fs::path like key in map (check standard)
  std::unordered_map<std::string, std::string> cache_;
};

void InitCache(Cache& cache);

} // namespace core

