#pragma once

#include <cstdint>
#include <filesystem>
#include <memory>

namespace logic
{

class LikeStorage final
{
public:
  void Set(uint64_t value) noexcept;
  uint64_t Get() const noexcept;
  void Increment() noexcept;

private:
  std::atomic<uint64_t> likesCount_{0};
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
