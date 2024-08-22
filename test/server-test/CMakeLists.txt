cmake_minimum_required(VERSION 3.10)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(test-server LANGUAGES C CXX)

if(NOT MSVC)
    find_program(CCACHE_PROGRAM ccache)
    if(CCACHE_PROGRAM)
        message(STATUS "Found CCache: ${CCACHE_PROGRAM}")
        set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE_PROGRAM})
        set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ${CCACHE_PROGRAM})
    endif()
endif()

file(GLOB_RECURSE sources CONFIGURE_DEPENDS ../../server/*.cpp main.cpp)
file(GLOB_RECURSE headers CONFIGURE_DEPENDS ../../server/*.h)

add_executable(main ${sources} ${headers})
target_include_directories(main PUBLIC ../../)

find_package(Threads REQUIRED)
target_link_libraries(main PUBLIC Threads)

set(THIRD_PARTY ../../thirdparty/fmt)
add_subdirectory(${THIRD_PARTY} build/thirdparty/fmt)
target_include_directories(main PUBLIC ../../thirdparty/fmt/include/)

add_custom_target(clang-format
    COMMAND clang-format -i ${sources} ${headers}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
