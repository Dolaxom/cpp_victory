#pragma once

#include <cstdint>
#include <filesystem>
#include <memory>

namespace logic
{

class LikeStorage
{
public:
  void Set(const uint64_t value);
  uint64_t Get() const noexcept;

private:
  uint64_t likesCount_;
};

class LikeManager
{
public:
  LikeManager(const std::filesystem::path& path);
  ~LikeManager();

  void Increment();
  uint64_t Get();

private:
  std::shared_ptr<LikeStorage> storage_;
  const std::filesystem::path& path_;

private:
  uint64_t ReadUint64FromFile();
  void WriteUint64InFile(uint64_t value);
};

} // namespace logic
