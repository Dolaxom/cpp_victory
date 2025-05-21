#pragma once

#include <csignal>
#include <functional>

namespace core::signals
{

inline std::function<void()> userCallback;

inline void InternalHandler(int signal)
{
  if (userCallback)
    userCallback();
}

inline void Setup(std::function<void()> callback)
{
  userCallback = std::move(callback);
  std::signal(SIGINT, InternalHandler);
  std::signal(SIGTERM, InternalHandler);
}

} // namespace core::signals
