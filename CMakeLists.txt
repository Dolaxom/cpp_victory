cmake_minimum_required(VERSION 3.15)
project(cpp_victory)

include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)

find_package(Crow REQUIRED)

add_executable(cpp_victory main.cpp)

target_link_libraries(cpp_victory Crow::Crow)

include_directories(source)
