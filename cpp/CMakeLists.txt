cmake_minimum_required(VERSION 3.22)

project(femson)
project(femson VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE
    src/femson.cpp
    src/input.cpp
    src/main.cpp)

add_executable(femson ${SOURCE})

include_directories(include/)

target_compile_options(femson PRIVATE
    -Werror               
    -Wextra             
    -Wpedantic
)