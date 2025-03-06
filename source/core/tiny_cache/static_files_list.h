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
  "bocchi_cpp.png",
  "book_img_1.png",
  "logo.png",
  "meme-pointers.jpg"
};

constexpr size_t size = sizeof(files) / sizeof(files[0]);

} // namespace static_dir
