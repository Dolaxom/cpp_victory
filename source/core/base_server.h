#pragma once

#include <iface/iserver.h>

#include <string>
#include <cstdint>

enum HttpStatus
{
  OK = 200,
  Created = 201,
  Accepted = 202,
  NoContent = 204,

  MovedPermanently = 301,
  Found = 302,
  NotModified = 304,

  BadRequest = 400,
  Unauthorized = 401,
  Forbidden = 403,
  NotFound = 404,
  MethodNotAllowed = 405,
  RequestTimeout = 408,
  Conflict = 409,

  InternalServerError = 500,
  NotImplemented = 501,
  BadGateway = 502,
  ServiceUnavailable = 503,
  GatewayTimeout = 504
};

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
