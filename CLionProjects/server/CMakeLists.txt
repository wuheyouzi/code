cmake_minimum_required(VERSION 2.8)
project(server)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(server main.cpp cpp_file_lib/error_response.cpp cpp_file_lib/get.cpp cpp_file_lib/handle.cpp cpp_file_lib/send.cpp)
