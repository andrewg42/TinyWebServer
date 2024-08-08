cmake_minimum_required(VERSION 3.10)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(webserver LANGUAGES C CXX)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS server/*.cpp server/*.c)
file(GLOB_RECURSE headers CONFIGURE_DEPENDS server/*.h)

add_executable(server ${sources} ${headers})

target_include_directories(server PUBLIC .)
