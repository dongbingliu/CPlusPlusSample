cmake_minimum_required(VERSION 3.17)
project(JsonUtils)

set(CMAKE_CXX_STANDARD 11)

include_directories(include/
        3rdparty/
        src/jsonutil/)

add_executable(JsonUtils sample/main.cpp src/jsonutil/CJsonUtils.cpp)