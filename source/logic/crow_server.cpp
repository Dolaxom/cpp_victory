#include <logic/crow_server.h>
#include <core/utils.h>

#include <cstdint>
#include <stdexcept>
#include <httplib/httplib.h>

constexpr auto indexhtml    = "index.html";
constexpr auto ru_indexhtml = "ru_index.html";

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

    CROW_ROUTE(rawCrowApp_, "/")([&](const crow::request& req) {
      std::string page = GetLocalizePageName(req);
      auto result = cache_.Get(page);
      if (!result.first) throw std::runtime_error("Where is " + page + "?");

      crow::response res{HttpStatus::OK, result.second};
      res.set_header("Content-Type", "text/html; charset=UTF-8");
      return res;
    });

    CROW_ROUTE(rawCrowApp_, "/<string>")([&](std::string path) {
      auto cacheResult = cache_.Get(path);
      if (cacheResult.first)
      {
        return crow::response{HttpStatus::OK, cacheResult.second};
      }
      else if (std::string data; core::Utils::GetStaticFile(path, data))
      {        
        return crow::response{HttpStatus::OK, data};
      }
      
      return crow::response{HttpStatus::NotFound};
    });
  }
  
  void CrowServer::Run()
  {
    rawCrowApp_.port(GetPort()).multithreaded().run();
  }

  std::string CrowServer::GetLocalizePageName(const crow::request& req)
  {
    std::string ip = req.get_header_value("X-Forwarded-For");
    if (ip.empty()) ip = req.remote_ip_address;

    static constexpr time_t delay = 500000;
    static const std::string apiUrl = "http://ip-api.com";
    httplib::Client cli(apiUrl);
    cli.set_connection_timeout(0, delay);
    cli.set_read_timeout(0, delay);
    auto ipResponse = cli.Get("/json/" + ip);

    bool youtubeBlocked = (ipResponse &&
      ipResponse->body.find("Russia") != ipResponse->body.npos);

    return youtubeBlocked ? ru_indexhtml : indexhtml;
  }

} // namespace logic
