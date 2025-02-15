#pragma once

namespace iface
{

struct IServer
{
  IServer() = default;
  IServer(const IServer& server) = delete;

  virtual ~IServer() = default;

  virtual void Setup() = 0;
  virtual void Run() = 0;
};

} // namespace iface
