add_library(liburing INTERFACE)
target_sources(liburing INTERFACE liburing.cpp)
target_include_directories(liburing INTERFACE liburing/src/include)

