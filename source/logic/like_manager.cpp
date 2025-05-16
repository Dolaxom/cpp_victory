#include <fstream>
#include <stdexcept>

#include "like_manager.h"

namespace logic
{

void LikeStorage::Set(const uint64_t value)
{
  likesCount_ = value;
}

uint64_t LikeStorage::Get() const noexcept
{
  return likesCount_;
}

LikeManager::LikeManager(const std::filesystem::path& path) : path_{path}
{
  std::ifstream file {path_};

  if (!file)
  {
    WriteUint64InFile(0);
  }

  storage_ = std::make_shared<LikeStorage>();
  storage_->Set(ReadUint64FromFile());
}

LikeManager::~LikeManager()
{
  WriteUint64InFile(Get());
}

void LikeManager::Increment()
{
  storage_->Set(storage_->Get() + 1);
}

uint64_t LikeManager::Get()
{
  return storage_->Get();
}

uint64_t LikeManager::ReadUint64FromFile()
{
  std::ifstream file{path_, std::ios::binary};
  if (!file)
    throw std::runtime_error("Can't open likes file-storage with filepath: " + path_.string());

  uint64_t value = 0;
  file.read(reinterpret_cast<char*>(&value), sizeof(value));

  if (!file)
    throw std::runtime_error("Failed to read uint64_t from binary file: " + path_.string());

  return value;
}

void LikeManager::WriteUint64InFile(uint64_t value)
{
  std::ofstream file{path_, std::ios::binary};
  if (!file)
    throw std::runtime_error("Can't create likes file-storage with filepath: " + path_.string());

  file.write(reinterpret_cast<const char*>(&value), sizeof(value));

  if (!file)
    throw std::runtime_error("Failed to write uint64_t to binary file: " + path_.string());
}

} // namespace logic
