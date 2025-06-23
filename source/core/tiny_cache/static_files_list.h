#pragma once

#include <cstring>

namespace static_dir
{

constexpr const char* files[] =
{
  "index.html",
  "ru_index.html",
  "styles.css",
  "script.js",
  "index_img_1.png",
  "index_img_2.png",
  "favicon.png",
  "index_img_3.jpg"
};

constexpr size_t size = sizeof(files) / sizeof(files[0]);

} // namespace static_dir
