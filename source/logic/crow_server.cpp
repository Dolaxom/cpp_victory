#include <logic/crow_server.h>

namespace logic
{

  CrowServer::CrowServer(CrowServer&& server) noexcept
    : BaseServer{std::move(server)} { }

  CrowServer::CrowServer(const std::string& address, uint32_t port)
    : BaseServer{address, port} { }

  CrowServer::CrowServer(std::string&& address, uint32_t port)
    : BaseServer{std::move(address), port} { }

  void CrowServer::Setup()
  {

  }
  
  void CrowServer::Run()
  {
    rawCrowApp_.port(GetPort()).multithreaded().run();
  }

} // namespace logic
