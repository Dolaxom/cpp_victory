#include <crow.h>

int main()
{
  core::Server server{"0.0.0.0", 11050};

  server.Run();
}
