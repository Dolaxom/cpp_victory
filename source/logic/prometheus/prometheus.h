#pragma once

#include <prometheus/counter.h>
#include <prometheus/exposer.h>
#include <prometheus/registry.h>

#include <memory>
#include <string>

namespace metrics {

class PrometheusClient {
 public:
  PrometheusClient(const std::string& address, uint32_t port);
  void IncrementRequestCounter(const std::string& path);

 private:
  prometheus::Exposer exposer_;
  std::shared_ptr<prometheus::Registry> registry_;
  prometheus::Family<prometheus::Counter>& reqCounter_;
};

}  // namespace metrics
