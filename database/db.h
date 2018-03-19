

#ifndef RPSGUI_DB_H
#define RPSGUI_DB_H
#include <driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include<stdio.h>
#include <iostream>

using namespace std;
using namespace sql;

class MySQLDB {
    static MySQLDB  *s_instance;
    sql::Driver *driver;
    sql::Connection *con;
    sql::PreparedStatement *prep_stmt;

   public:
     MySQLDB();
    static MySQLDB *instance();
    void insert_data(string game_id,string player, int rock, int paper, int scissors);
    void close();
};
#endif //RPSGUI_DB_H
