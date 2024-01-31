#pragma once

#include <memory>
#include <mysql/mysql.h>

namespace webserver {
namespace sql {

class SQL_Conn {
public:
  // TODO
  SQL_Conn() : p_mysql(mysql_init(nullptr)) {}
  SQL_Conn &operator=(SQL_Conn &&) = delete;
  ~SQL_Conn() {
  }

private:
  std::shared_ptr<MYSQL> p_mysql;
};

} // namespace sql
} // namespace webserver
