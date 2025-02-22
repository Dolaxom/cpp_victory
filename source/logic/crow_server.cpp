#include <logic/crow_server.h>
#include <core/utils.h>

#include <stdexcept>

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
    core::InitCache(cache_);

    CROW_ROUTE(rawCrowApp_, "/")([&](){
      auto result = cache_.Get("index.html");
      if (!result.first) throw std::runtime_error("Where is index.html?");

      crow::response res{200, result.second};
      res.set_header("Content-Type", "text/html; charset=UTF-8");
      return res;
    });

    CROW_ROUTE(rawCrowApp_, "/<string>")([&](std::string path) {
      auto cacheResult = cache_.Get(path);
      if (cacheResult.first)
      {
        return crow::response{200, cacheResult.second};
      }
      else if (std::string data; core::Utils::GetStaticFile(path, data))
      {        
        return crow::response{200, data};
      }
      
      return crow::response{404};
    });
  }
  
  void CrowServer::Run()
  {
    rawCrowApp_.port(GetPort()).multithreaded().run();
  }

} // namespace logic
