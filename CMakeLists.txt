cmake_minimum_required(VERSION 3.20)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(webserver LANGUAGES C CXX)

file(GLOB_RECURSE webserver_sources CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE webserver_headers CONFIGURE_DEPENDS include/*.h)

add_executable(server ${webserver_sources} ${webserver_headers})
target_include_directories(server PUBLIC include)

find_package(Threads REQUIRED)
target_link_libraries(server PUBLIC Threads::Threads)

