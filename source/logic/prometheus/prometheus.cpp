#include "prometheus.h"

namespace metrics {

PrometheusClient::PrometheusClient(const std::string& address, uint32_t port)
    : exposer_{address + ":" + std::to_string(port)},
      registry_{std::make_shared<prometheus::Registry>()},
      reqCounter_{prometheus::BuildCounter()
                      .Name("http_requests_total")
                      .Help("Total number of HTTP(s) requests")
                      .Register(*registry_)}
{
  exposer_.RegisterCollectable(registry_);
}

void PrometheusClient::IncrementRequestCounter(const std::string& path) {
  reqCounter_.Add({{"path", path}}).Increment();
}

}  // namespace metrics
