# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.28
cmake_policy(SET CMP0009 NEW)

# webserver_headers at CMakeLists.txt:13 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/home/andy/project/WebServer/test/log-test/../../include/*.h")
set(OLD_GLOB
  "/home/andy/project/WebServer/test/log-test/../../include/Config.h"
  "/home/andy/project/WebServer/test/log-test/../../include/Sigflow.h"
  "/home/andy/project/WebServer/test/log-test/../../include/Webserver.h"
  "/home/andy/project/WebServer/test/log-test/../../include/log/Buffer.h"
  "/home/andy/project/WebServer/test/log-test/../../include/log/Log.h"
  "/home/andy/project/WebServer/test/log-test/../../include/net/Acceptor.h"
  "/home/andy/project/WebServer/test/log-test/../../include/net/Handler.h"
  "/home/andy/project/WebServer/test/log-test/../../include/net/Http_Conn.h"
  "/home/andy/project/WebServer/test/log-test/../../include/net/Reactor.h"
  "/home/andy/project/WebServer/test/log-test/../../include/sql/SQL_Conn.h"
  "/home/andy/project/WebServer/test/log-test/../../include/threadpool/Thread_Pool.h"
  "/home/andy/project/WebServer/test/log-test/../../include/timer/Time_Heap.h"
  "/home/andy/project/WebServer/test/log-test/../../include/timer/Timer.h"
  "/home/andy/project/WebServer/test/log-test/../../include/utils/Blocking_Queue.h"
  "/home/andy/project/WebServer/test/log-test/../../include/utils/Macros.h"
  "/home/andy/project/WebServer/test/log-test/../../include/utils/Noncopyable.h"
  "/home/andy/project/WebServer/test/log-test/../../include/utils/Singleton.h"
  "/home/andy/project/WebServer/test/log-test/../../include/utils/Spin_Lock.h"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/home/andy/project/WebServer/test/log-test/build/CMakeFiles/cmake.verify_globs")
endif()

# webserver_sources at CMakeLists.txt:14 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/home/andy/project/WebServer/test/log-test/../../src/*.cpp")
set(OLD_GLOB
  "/home/andy/project/WebServer/test/log-test/../../src/log/Buffer.cpp"
  "/home/andy/project/WebServer/test/log-test/../../src/log/Log.cpp"
  "/home/andy/project/WebServer/test/log-test/../../src/net/Acceptor.cpp"
  "/home/andy/project/WebServer/test/log-test/../../src/net/Reactor.cpp"
  "/home/andy/project/WebServer/test/log-test/../../src/server.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/home/andy/project/WebServer/test/log-test/build/CMakeFiles/cmake.verify_globs")
endif()
