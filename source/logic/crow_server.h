#pragma once

#include <core/tiny_cache/cache.h>
#include <core/base_server.h>
#include <crow.h>

#include "prometheus/prometheus.h"
#include "like_manager.h"

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
  void Stop() override;

private:
  metrics::PrometheusClient prometheusClnt_;
  crow::SimpleApp rawCrowApp_;
  core::Cache cache_;
  logic::LikeManager likesManager_;

private:
  std::string GetLocalizePageName(const crow::request& req);
};

} // namespace logic
