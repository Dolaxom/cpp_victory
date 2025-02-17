#pragma once

#include <iface/iserver.h>

#include <string>
#include <cstdint>

namespace core
{

class BaseServer : public interfaces::IServer
{
public:
  BaseServer() = delete;
  BaseServer(const BaseServer& server) = delete;
  BaseServer(BaseServer&& server) noexcept;

  BaseServer(const std::string& address, uint32_t port);
  BaseServer(std::string&& address, uint32_t port);

  const std::string& GetAddress() const;
  uint32_t GetPort() const;

  void Setup() override = 0;
  void Run() override = 0;

private:
  std::string address_;
  uint32_t port_;
};

} // namespace core
