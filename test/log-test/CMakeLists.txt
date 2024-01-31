cmake_minimum_required(VERSION 3.20)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(UT_log LANGUAGES C CXX)

file(GLOB_RECURSE webserver_headers CONFIGURE_DEPENDS ../../include/*.h)
file(GLOB_RECURSE webserver_sources CONFIGURE_DEPENDS ../../src/*.cpp)
list(FILTER webserver_sources EXCLUDE REGEX "../../src/server.cpp")

find_package(Threads REQUIRED)

add_executable(log_test ${webserver_headers} ${webserver_sources} log_test.cpp)
target_include_directories(log_test PUBLIC ../../include)
target_link_libraries(log_test PUBLIC Threads::Threads)
