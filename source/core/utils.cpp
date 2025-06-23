#include <core/utils.h>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace fs = std::filesystem;

namespace core::utils
{

error_type StaticContent::GetFile(const std::filesystem::path& path, std::string& data)
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

bool IsNumber(const std::string& s)
{
  return !s.empty() && std::find_if(s.begin(), 
      s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

DotEnv::DotEnv()
{
  constexpr auto path = ".env";
  
  std::ifstream file {path};
  if (!file.is_open())
  {
    throw std::runtime_error("Can't find '.env' file in DotEnv::DotEnv()");
  }

  std::string str;
  while (std::getline(file, str))
  {
    size_t idx = str.find('=');
    if (idx == std::string::npos) 
      continue;
    std::string key = str.substr(0, idx);
    std::string value = str.substr(idx + 1);
    if (IsNumber(value))
      data_[std::move(key)] = std::stoi(std::move(value));
    else
      data_[std::move(key)] = std::move(value);
  }

  file.close();
}

DotEnv& DotEnv::Instance()
{
  static DotEnv obj{};

  return obj;
}

std::optional<DotEnv::value_type> DotEnv::GetValue(const std::string& key)
{
  if (data_.contains(key))
  {
    return data_[key];
  }

  return std::nullopt;
}

} // namespace core::utils
