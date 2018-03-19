
#include "db.h"
#include<iostream>
#include <mysql_connection.h>
#include <driver.h>
#include <cppconn/exception.h>
#include<stdio.h>
#include <iostream>

using namespace std;
using namespace sql;

/**
 * Singleton pattern for database to have only one connection open
 */
MySQLDB* MySQLDB::s_instance = NULL;

 MySQLDB* MySQLDB:: instance()
{
    if (!s_instance)
        s_instance = new MySQLDB;
    return s_instance;
}

MySQLDB ::MySQLDB() {
    try {


        cout << "connecting to mysql server....";
        driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "root", "root");
        cout << "connected" << endl;
        con->setSchema("rps");
    }catch (sql::SQLException &e) {

    }

    }

void MySQLDB ::insert_data(string game_id, string player, int rock, int paper, int scissors) {
    try {
        prep_stmt = con->prepareStatement(
                "INSERT INTO game_details(game_id,player,rock,paper,scissors) VALUES(?,?,?,?,?)");

        prep_stmt->setString(1, game_id);
        prep_stmt->setString(2, player);
        prep_stmt->setInt(3, rock);
        prep_stmt->setInt(4, paper);
        prep_stmt->setInt(5, scissors);
        prep_stmt->execute();
    }catch (sql :: SQLException &e){

    }
}

void MySQLDB :: close(){
    try {


        cout << "connection \n";
        con->close();
    }catch (sql :: SQLException &e){
        
    }
}

