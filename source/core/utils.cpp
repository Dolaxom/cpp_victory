#include <core/utils.h>
#include <fstream>
#include <sstream>

namespace fs = std::filesystem;

namespace core::utils
{

  StaticContent::error StaticContent::GetFile(const std::filesystem::path& path, std::string& data)
  {
    fs::path staticDir = fs::canonical("static");
    fs::path requestedFile = fs::weakly_canonical(staticDir / path);

    for (auto b = staticDir.begin(), p = requestedFile.begin(); b != staticDir.end(); ++b, ++p)
    {
      if (p == requestedFile.end() || *p != *b)
      {
        return false;
      }
    }

    std::ifstream file{requestedFile};
    if (!file)
    {
      return false;
    }

    std::ostringstream content;
    content << file.rdbuf();
    data = content.str();

    return true;
  }

} // namespace core::utils
