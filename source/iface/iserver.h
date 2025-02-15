#pragma once

namespace iface
{

struct IServer
{
  IServer() = default;
  IServer(const IServer& server) = delete;
};

} // namespace iface
