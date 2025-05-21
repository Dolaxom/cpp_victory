#include <logic/crow_server.h>
#include <core/signals_handler.h>

#include <stdexcept>
#include <iostream>
#include <memory>

int main()
{
  std::shared_ptr<interfaces::IServer> server =
    std::make_shared<logic::CrowServer>("0.0.0.0", 11050);

  try
  {
    core::signals::Setup([&server]() {
      server->Stop();
    });

    server->Setup();
    server->Run();
  }
  catch (const std::exception& ex)
  {
    std::cerr << "Server exception, ex = " << ex.what();
  }
}
