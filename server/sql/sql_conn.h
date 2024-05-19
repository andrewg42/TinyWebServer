#pragma once

#include <memory>
#include <mysql/mysql.h>

namespace webserver {
namespace sql {

class SQL_Conn {
private:
    std::shared_ptr<MYSQL> p_mysql;

public:
    // TODO
    SQL_Conn();
    ~SQL_Conn();
};

} // namespace webserver::sql
} // namespace webserver