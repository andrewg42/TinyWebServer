cmake_minimum_required(VERSION 3.20)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(UT_timer LANGUAGES C CXX)

file(GLOB_RECURSE webserver_headers CONFIGURE_DEPENDS ../webserver/*.h)
file(GLOB_RECURSE webserver_sources CONFIGURE_DEPENDS ../webserver/*.cpp)

find_package(Threads REQUIRED)

add_executable(timer_test ${webserver_headers} ${webserver_sources} timer_test.cpp)
target_include_directories(UT_timer PUBLIC ../webserver)
target_link_libraries(UT_timer PUBLIC Threads::Threads)
