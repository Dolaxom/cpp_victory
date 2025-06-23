#include <logic/crow_server.h>
#include <core/signals_handler.h>
#include <core/utils.h>

#include <stdexcept>
#include <iostream>
#include <memory>

int main()
{
  core::utils::DotEnv::Instance();
  std::shared_ptr<interfaces::IServer> server =
    std::make_shared<logic::CrowServer>(
      std::get<std::string>(core::utils::DotEnv::Instance().GetValue("SERVER_ADDR").value()),
      std::get<int32_t>(core::utils::DotEnv::Instance().GetValue("SERVER_PORT").value())
    );

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
