cmake_minimum_required(VERSION 3.15)
project(cpp_victory)

include(${CMAKE_BINARY_DIR}/generators/conan_toolchain.cmake)

find_package(Crow REQUIRED)

add_executable(cpp_victory
  source/main.cpp

  source/core/base_server.cpp
  source/core/utils.cpp
  source/logic/crow_server.cpp

  source/iface/iserver.h
  source/core/base_server.h
  source/core/utils.h
  source/logic/crow_server.h
)

target_link_libraries(cpp_victory Crow::Crow)

include_directories(source)
