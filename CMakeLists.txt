cmake_minimum_required(VERSION 3.15)
project(cpp_victory)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(${CMAKE_BINARY_DIR}/generators/conan_toolchain.cmake)

find_package(Crow REQUIRED)
find_package(httplib REQUIRED)
find_package(prometheus-cpp REQUIRED)

set(SOURCES
  source/main.cpp
  source/core/base_server.cpp
  source/core/utils.cpp
  source/core/tiny_cache/cache.cpp
  source/logic/crow_server.cpp
  source/logic/prometheus/prometheus.cpp
)

set(HEADERS
  source/iface/iserver.h
  source/core/base_server.h
  source/core/utils.h
  source/core/tiny_cache/cache.h
  source/core/tiny_cache/static_files_list.h
  source/logic/crow_server.h
  source/logic/prometheus/prometheus.h
)

add_executable(cpp_victory ${SOURCES} ${HEADERS})

target_link_libraries(cpp_victory Crow::Crow httplib::httplib prometheus-cpp::prometheus-cpp)

target_include_directories(cpp_victory PRIVATE source)
