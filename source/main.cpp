#include <logic/crow_server.h>

#include <stdexcept>
#include <iostream>
#include <memory>

int main()
{
  std::unique_ptr<interfaces::IServer> server =
    std::make_unique<logic::CrowServer>("0.0.0.0", 11050);

  try
  {
    server->Setup();
    server->Run();
  }
  catch (const std::exception& ex)
  {
    std::cerr << "Server exception, ex = " << ex.what();
  }
}
