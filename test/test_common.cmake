set(proj_name "UT_${mod}")
set(exe_name "${mod}_test")
set(src_name "${mod}_test.cpp")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(${proj_name} LANGUAGES C CXX)

file(GLOB_RECURSE webserver_headers CONFIGURE_DEPENDS ../../server/${mod}/*.h)
file(GLOB_RECURSE webserver_sources CONFIGURE_DEPENDS ../../server/${mod}/*.cpp)
list(FILTER webserver_sources EXCLUDE REGEX "../../server/server.cpp")

find_package(Threads REQUIRED)

add_executable(${exe_name} ${webserver_headers} ${webserver_sources} ${src_name})
target_include_directories(${exe_name} PUBLIC ../../include)
target_link_libraries(${exe_name} PUBLIC Threads::Threads)