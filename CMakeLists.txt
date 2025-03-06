cmake_minimum_required(VERSION 3.15)
project(cpp_victory)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(${CMAKE_BINARY_DIR}/generators/conan_toolchain.cmake)

find_package(Crow REQUIRED)
find_package(httplib REQUIRED)

add_executable(cpp_victory
  source/main.cpp

  source/core/base_server.cpp
  source/core/utils.cpp
  source/core/tiny_cache/cache.cpp
  source/logic/crow_server.cpp

  source/iface/iserver.h
  source/core/base_server.h
  source/core/utils.h
  source/core/tiny_cache/cache.h
  source/core/tiny_cache/static_files_list.h
  source/logic/crow_server.h
)

target_link_libraries(cpp_victory Crow::Crow httplib::httplib)

include_directories(source)
