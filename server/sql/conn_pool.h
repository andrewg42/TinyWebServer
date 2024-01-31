#pragma once

#include <server/sql/sql_conn.h>
#include <server/utils/singleton.h>

namespace webserver {
namespace sql {

struct Conn_Pool : utils::Singleton<Conn_Pool> {};

} // namespace sql
} // namespace server
