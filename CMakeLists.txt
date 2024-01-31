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

add_executable(main ${sources} ${headers})

target_include_directories(main PUBLIC .)

find_package(Threads REQUIRED)
target_link_libraries(main PUBLIC Threads)

set(THIRD_PARTY thirdparty)
add_subdirectory(${THIRD_PARTY})
