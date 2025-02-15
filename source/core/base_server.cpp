#include <core/base_server.h>

namespace core
{

  BaseServer::BaseServer(BaseServer&& server) noexcept
  {
    std::swap(address_, server.address_);
    std::swap(port_, server.port_);
  }

  BaseServer::BaseServer(const std::string& address, uint32_t port)
    : address_{address}, port_{port} { }

  BaseServer::BaseServer(std::string&& address, uint32_t port)
    : address_{std::move(address)}, port_{port} { }

  const std::string& BaseServer::GetAddress() const
  {
    return address_;
  }

  uint32_t BaseServer::GetPort() const
  {
    return port_;
  }

} // namespace core
