#pragma once

namespace webserver {

namespace utils {

#define WEBSERVER_STRINGIZE_HELPER(x) #x

#define WEBSERVER_STRINGIZE(x) WEBSERVER_STRINGIZE_HELPER(x)

#define WEBSERVER_GET_LOCATE (__FILE__ ": line = " WEBSERVER_STRINGIZE(__LINE__) "\n")

#define WEBSERVER_CONCAT(x, y) x##y

} // webserver::utils

} // webserver
