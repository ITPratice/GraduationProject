#include "data_manager.h"

data_manager::data_manager() {

}

data_manager::~data_manager() {

}

void data_manager::db_open(const char* db_path) {
    if(sqlite3_open_v2(db_path, &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_FULLMUTEX, NULL) == SQLITE_OK) {
        db_create_tb();
    }
    std::cout << "Connect databse successfully\n";
}

void data_manager::db_close() {
    if (db != NULL) {
        sqlite3_close(db);
        db = NULL;
        std::cout << "DATA_MANAGER - Disconnect database successfully\n" ;
    }
}

void data_manager::db_create_tb() {
    char *zErrMsg = 0;
    int rc;
    char *sql;

    sql = "CREATE TABLE USER("                                          \
            "ID             NVARCHAR(10)    PRIMARY KEY     NOT NULL,"  \
            "EMAIL          NVARCHAR(100)                   NOT NULL,"  \
            "ADDRESS        NVARCHAR(100)                   NOT NULL,"  \
            "PHONE_NUMBER   NVARCHAR(100)                   NOT NULL,"  \
            "PASSWORD       NVARCHAR(100)                   NOT NULL,"  \
            "NUMBER_PLATE   NVARCHAR(100)                   NOT NULL,"  \
            "TYPE           INT                             NOT NULL);";
    rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return;
    } else {
        std::cout << "DATA_MANAGER - Table USER created successfully\n";
    }

    sql = "CREATE TABLE LOCATION("                                      \
            "ID             NVARCHAR(10)    PRIMARY KEY     NOT NULL,"  \
            "LAT_POINT      NVARCHAR(20)                    NOT NULL,"  \
            "LON_POINT      NVARCHAR(20)                    NOT NULL);";
    rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return;
    } else {
        std::cout << "DATA_MANAGER - Table LOCATION created successfully\n";
    }

    sql = "CREATE TABLE USER_LOCATION("                                     \
            "USER_ID        NVARCHAR(10)                    NOT NULL,"      \
            "LOCATION_ID    NVARCHAR(10)                    NOT NULL,"      \
            "TIME           NVARCHAR(20)                    NOT NULL,"     \
            "PRIMARY KEY (USER_ID, LOCATION_ID),"                           \
            "FOREIGN KEY (USER_ID) REFERENCES USER(ID) ON DELETE CASCADE,"  \
            "FOREIGN KEY (LOCATION_ID) REFERENCES LOCATION(ID) ON DELETE CASCADE);";
    rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return;
    } else {
        std::cout << "DATA_MANAGER - Table USER_LOCATION created successfully\n";
    }
}