#pragma once

#include <core/base_server.h>
#include <crow.h>

namespace logic
{

class CrowServer final : public core::BaseServer
{
public:
  CrowServer(CrowServer&& server) noexcept;

  CrowServer(const std::string& address, uint32_t port);
  CrowServer(std::string&& address, uint32_t port);

  void Setup() override;
  void Run() override;

private:
  crow::SimpleApp rawCrowApp_;
};

} // namespace logic
