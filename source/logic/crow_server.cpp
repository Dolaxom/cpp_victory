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
    : BaseServer{std::move(server)}, prometheusClnt_{"0.0.0.0", 9091} { }

  CrowServer::CrowServer(const std::string& address, uint32_t port)
    : BaseServer{address, port}, prometheusClnt_{"0.0.0.0", 9091} { }

  CrowServer::CrowServer(std::string&& address, uint32_t port)
    : BaseServer{std::move(address), port}, prometheusClnt_{"0.0.0.0", 9091} { }

  /**
   * @brief Сonfigure basic server settings.
   *
   * Сonfigure basic server settings, such as tiny-cache 
   * initialization and declaring server endpoints.
   *
   * @return It doesn't return anything, but it can throw an exception.
   *
   * @details
   * It can throw a standard exception inherited from std::exception,
   * so a try-catch block is required!
   *
   * @usage
   * CrowServer server("0.0.0.0", 11050);
   * server.Setup();
   * server.Run();
   */
  void CrowServer::Setup()
  {
    core::InitCache(cache_);

    CROW_ROUTE(rawCrowApp_, "/")([&](const crow::request& req) {
      prometheusClnt_.IncrementRequestCounter("/");
      std::string page = GetLocalizePageName(req);
      auto result = cache_.Get(page);
      if (!result.first) throw std::runtime_error("Where is " + page + "?");

      crow::response res{HttpStatus::OK, result.second};
      res.set_header("Content-Type", "text/html; charset=UTF-8");
      return res;
    });

    CROW_ROUTE(rawCrowApp_, "/<string>")([&](std::string path) {
      prometheusClnt_.IncrementRequestCounter(path);
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
  
  /**
   * @brief Standard launch of the CrowCpp server.
   */
  void CrowServer::Run()
  {
    rawCrowApp_.port(GetPort()).multithreaded().run();
  }

  /**
   * @brief Select the desired version index.html pages.
   *
   * Selects a Russian page or an international page
   * with different video players (Youtube/Rutube).
   *
   * @return Page filename.
   *
   * @details
   * It's just a private helper function for
   * handling the root of a website ('/' page).
   *
   * @usage
   * std::string page = GetLocalizePageName(request);
   */
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
