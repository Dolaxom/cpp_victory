#pragma once

namespace interfaces
{

struct IServer
{
  IServer() = default;
  IServer(const IServer& server) = delete;

  virtual ~IServer() = default;

  virtual void Setup() = 0;
  virtual void Run() = 0;
  virtual void Stop() = 0;
};

} // namespace interfaces
