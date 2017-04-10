#include <sqlite3.h>
#include <iostream>
#include <string>

class data_manager {
public:
    data_manager();
    ~data_manager();
public:
    static void db_open(const char* db_path);
    static void db_close();
    static void db_create_tb();
private:
    sqlite3 *db;
};