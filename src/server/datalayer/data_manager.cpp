#include "data_manager.h"
#include "../stdafx.h"

DataManager::DataManager() {
    db_file_path = "";
    db = NULL;
    isConnect = false;
}

DataManager::DataManager(std::string pathFile) {
    db_file_path = pathFile;
    db = NULL;
    isConnect = false;
}

DataManager::~DataManager() {
    if(isConnect) {
        if(db != NULL) {
            sqlite3_close(db);
            std::cout << "DATA_MANAGER - Disconnect database Successfully" << std::endl;
            db = NULL;
        }
        isConnect = false;
    }
}

static int callback(void *data, int argc, char **argv, char **azColName) {
    return 0;
}

ResponseCode DataManager::createDb() {
    char *zErrMsg = 0;
    int rc;
    char *sql;

    // Open database
    rc = sqlite3_open(db_file_path.c_str(), &db);
    if(rc) {
        fprintf(stderr, "DATA_MANAGER - Can't open database: %s\n", sqlite3_errmsg(db));
        return DATA_ERROR_OPEN_DB;
    } else {
        fprintf(stdout, "DATA_MANAGER - Opened database successfully\n");
    }

    // Create USERS table
    sql = (char *)"CREATE TABLE USER   ("                                           \
            "ID             INTEGER         PRIMARY KEY AUTOINCREMENT   NOT NULL,"  \
            "EMAIL          NVARCHAR(50)                                NOT NULL,"  \
            "USERNAME       NVARCHER(20)                                NOT NULL,"  \
            "ADDRESS        NVARCHAR(100)                               NOT NULL,"  \
            "PHONE_NUMBER   NVARCHAR(15)                                NOT NULL,"  \
            "FULL_NAME      NVARCHAR(50)                                NOT NULL,"  \
            "PASSWORD       NVARCHAR(20)                                NOT NULL,"  \
            "ROLE           INTEGER                                     NOT NULL);";
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return DATA_ERROR_CREATE_TB;
    } else {
        fprintf(stdout, "DATA_MANAGER - Table USERS created successfully\n");
    }

    // Cretae Vehicle_type table
    sql = (char *)"CREATE TABLE VEHICLE_TYPE    ("                                  \
            "ID             INTEGER         PRIMARY KEY AUTOINCREMENT   NOT NULL,"  \
            "NAME           NVARCHAR(10)                                NOT NULL);";
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return DATA_ERROR_CREATE_TB;
    } else {
        fprintf(stdout, "DATA_MANAGER - Table VEHICLE_TYPE created successfully\n");
    }

    // Create VEHICLES table
    sql = (char *)"CREATE TABLE VEHICLE    ("                                   \
            "NUMBER_PLATE       NVARCHAR(10)    PRIMARY KEY         NOT NULL,"  \
            "BRANCH_ID          INTEGER                             NOT NULL,"  \
            "HARDWARE_ID        NVARCHAR(10)                                ,"  \
            "DESCRIPTION        NVARCHAR(100)                               ,"  \
            "TYPE_ID            INTEGER                             NOT NULL,"  \
            "FOREIGN KEY (TYPE_ID)   REFERENCES VEHICLE_TYPE(ID)    ON DELETE CASCADE);";
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return DATA_ERROR_CREATE_TB;
    } else {
        fprintf(stdout, "DATA_MANAGER - Table VEHICLE created successfully\n");
    }

    // Create USERS_CARS table
    sql = (char *)"CREATE TABLE USER_VEHICLE  (" \
            "USER_ID                                INTEGER                             NOT NULL            ,"  \ 
            "VEHICLE_NUMBER_PLATE                   NVARCHAR(10)                        NOT NULL            ,"  \ 
            "PRIMARY KEY (USER_ID, VEHICLE_NUMBER_PLATE)                                                    ,"  \ 
            "FOREIGN KEY (USER_ID)                  REFERENCES USER(ID)                 ON DELETE CASCADE   ,"  \
            "FOREIGN KEY (VEHICLE_NUMBER_PLATE)     REFERENCES VEHICLE(NUMBER_PLATE)    ON DELETE CASCADE)  ;";
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return DATA_ERROR_CREATE_TB;
    } else {
        fprintf(stdout, "DATA_MANAGER - Table USER_VEHICLE created successfully\n");
    }

    // Create TRACKING table
    sql = (char *)"CREATE TABLE TRACKING  (" \
            "ID                 INTEGER         PRIMARY KEY AUTOINCREMENT   NOT NULL,"              \       
            "LATITUDE           NVARCHAR(20)                                NOT NULL,"              \
            "LONGITUDE          NVARCHAR(20)                                NOT NULL);";
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return DATA_ERROR_CREATE_TB;
    } else {
        fprintf(stdout, "DATA_MANAGER - Table TRACKING created successfully\n");
    }

    sql = (char *)"CREATE TABLE ROUTE ("\
            "VEHICLE_NUMBER_PLATE               NVARCHAR(10)                        NOT NULL"           \
            "LOCATION_ID                        INTEGER                             NOT NULL"           \
            "START_DATE                         NVARCHER(10)                        NOT NULL"           \
            "START_TIME                         NVARCHAR(10)                        NOT NULL"           \
            "END_DATE                           NVARCHAR(10)                        NOT NULL"           \
            "END_TIME                           NVARCHAR(10)                        NOT NULL"           \
            "PRIMARY KEY (VEHICLE_NUMBER_PLATE, LOCATION_ID)"                                           \
            "FOREIGN KEY (VEHICLE_NUMBER_PLATE) REFERENCES VEHICLE(NUMBER_PLATE)    ON DELETE CASCADE"  \
            "FOREIGN KEY (LOCATION_ID)          REFERENCES  TRACKING(ID)            ON DELETE CASCADE);";
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return DATA_ERROR_CREATE_TB;
    } else {
        fprintf(stdout, "DATA_MANAGER - Table ROUTE created successfully\n");
    }

    sql = (char *)"CREATE TABLE BRANCH("\
            "BRANCH_ID      INTEGER         PRIMARY KEY AUTOINCREMENT   NOT NULL"   \
            "NAME           NVARCHAR(50)                                NOT NULL);";
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return DATA_ERROR_CREATE_TB;
    } else {
        fprintf(stdout, "DATA_MANAGER - Table BRANCH created successfully\n");
    }
    return DATA_SUCCESS;
}

bool DataManager::dbIsExist() {
    std::cout << "DATA_MANAGER - File .db full name: " << db_file_path << std::endl;

    char* sql = (char *)"SELECT name FROM sqlite_master WHERE type='table' AND name='USER';";

    sqlite3_stmt *statement;
    if (sqlite3_prepare(db, sql, -1, &statement, 0) == SQLITE_OK) {
        int res = 0;
        res = sqlite3_step(statement);
        if (res != SQLITE_ROW) {
            sqlite3_finalize(statement);
            sqlite3_close(db);
            return false;
        }
    } else {
        sqlite3_close(db);
        return false;
    }
    sqlite3_finalize(statement);
    sqlite3_close(db);

    return true;
}

ResponseCode DataManager::connectDb() {
    // if (!dbIsExist()) {
    //     std::cout << "DATA_MANAGER - Start create DB\n";
    //     ResponseCode ret = createDb();
    //     if (ret != DATA_SUCCESS) {
    //         return ret;
    //     }
    // }

    int rc = sqlite3_open(db_file_path.c_str(), &db);
    if(rc) {
        fprintf(stderr, "DATA_MANAGER - Can't open database: %s\n", sqlite3_errmsg(db));
        return DATA_ERROR_OPEN_DB;
    } else {
        fprintf(stderr, "DATA_MANAGER - Opened database successfully\n");
    }

    isConnect = true;
    return DATA_SUCCESS;
}

ResponseCode DataManager::disconnectDb() {
    if (isConnect) {
        if (db != NULL) {
            sqlite3_close(db);
            db = NULL;
            printf("DATA_MANAGER - Disconnect database successfully\n") ;
        }
        isConnect = false;
    }
    return DATA_SUCCESS;
}

ResponseCode DataManager::GetAllUser(std::vector<User>& lstUser) {
    sqlite3_stmt *stmt;
    const char* query = (char *)"SELECT * FROM USER;";
    if(sqlite3_prepare(db, query, -1, &stmt, 0) == SQLITE_OK) {
        int res = 0;
        while (true)
        {
            res = sqlite3_step(stmt);

            if (res == SQLITE_ROW) {
                User user;
                user.setEmail((char*)sqlite3_column_text(stmt, 1));
                user.setUsername((char*)sqlite3_column_text(stmt, 2));
                user.setAddress((char*)sqlite3_column_text(stmt, 3));
                user.setPhoneNumber((char*)sqlite3_column_text(stmt, 4));
                user.setFullname((char*)sqlite3_column_text(stmt, 5));
                user.setPassword((char*)sqlite3_column_text(stmt, 6));
                lstUser.push_back(user);
            }

            if ( res == SQLITE_DONE || res == SQLITE_ERROR)
            {
                std::cout << "Get all user finish " << std::endl;
                break;
            }
        }
        sqlite3_finalize(stmt);
    } else {
        return DATA_ERROR_SELECT_DB;
    }
    return DATA_SUCCESS;
}

ResponseCode DataManager::Login(std::string email, std::string password) {
    std::stringstream strm;
    strm << "SELECT * FROM USER WHERE EMAIL = '" << email << "' AND PASSWORD = '" << password << "';";
    std::string s = strm.str();
    char *str = &s[0];
    sqlite3_stmt *statement;
    char *query = str;
    if(sqlite3_prepare(db, query, -1, &statement, 0) == SQLITE_OK) {
        int ctotal = sqlite3_column_count(statement);
        int res;
        while(true) {
            res = sqlite3_step(statement);
            if (res == SQLITE_ROW) {
                break;
            } 
            return DATA_ERROR_SELECT_DB;
        }
    } else {
        return DATA_ERROR_SELECT_DB;
    }
    return DATA_SUCCESS;
}

// User
ResponseCode DataManager::InsertUser(User &user) {
   /* "CREATE TABLE USER   ("                                           \
            "ID             INTEGER         PRIMARY KEY AUTOINCREMENT   NOT NULL,"  \
            "EMAIL          NVARCHAR(50)                                NOT NULL,"  \
            "USERNAME       NVARCHER(20)                                NOT NULL,"  \
            "ADDRESS        NVARCHAR(100)                               NOT NULL,"  \
            "PHONE_NUMBER   NVARCHAR(15)                                NOT NULL,"  \
            "FULL_NAME      NVARCHAR(50)                                NOT NULL,"  \
            "PASSWORD       NVARCHAR(20)                                NOT NULL,"  \
            "ROLE           INTEGER                                     NOT NULL);" */
    std::stringstream strm;
    strm << "INSERT INTO USER (EMAIL, USERNAME, ADDRESS, PHONE_NUMBER, FULL_NAME, PASSWORD, ROLE) values ('"
         << user.getEmail()
         << "','" << user.getUsername()
         << "','" << user.getAddress()
         << "','" << user.getPhoneNumber()
         << "','" << user.getFullname()
         << "','" << user.getPassword()
         << "','" << user.getRole()
         << "');";
         
    std::string temp = strm.str();
    std::cout << "DATA_MANAGER - Query InsertUser: " << temp << std::endl;

    char *query = &temp[0];
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "DATA_MANAGER - SQL error: %s\n", zErrMsg);
        return DATA_ERROR_INSERT_TB;
    } else {
        std::cout << "DATA_MANAGER - Insert User successfully" << std::endl;
    }
    return DATA_SUCCESS;
}

ResponseCode DataManager::UpdateUser(User &user) {
   /* "CREATE TABLE USER   ("                                           \
            "ID             INTEGER         PRIMARY KEY AUTOINCREMENT   NOT NULL,"  \
            "EMAIL          NVARCHAR(50)                                NOT NULL,"  \
            "USERNAME       NVARCHER(20)                                NOT NULL,"  \
            "ADDRESS        NVARCHAR(100)                               NOT NULL,"  \
            "PHONE_NUMBER   NVARCHAR(15)                                NOT NULL,"  \
            "FULL_NAME      NVARCHAR(50)                                NOT NULL,"  \
            "PASSWORD       NVARCHAR(20)                                NOT NULL,"  \
            "ROLE           INTEGER                                     NOT NULL);" */
    std::stringstream strm;
    strm << "UPDATE USER SET"
         << "EMAIL = '" << user.getEmail() << "',"
         << "USERNAME = '" << user.getUsername() << "',"
         << "ADDRESS = '" << user.getAddress() << "',"
         << "PHONE_NUMBER = '" << user.getPhoneNumber() << "',"
         << "FULL_NAME = '" << user.getFullname() << "',"
         << "PASSWORD = '" << user.getPassword() << "',"
         << "ROLE = '" << user.getRole() << "',"
         << "WHERE ID = '" << user.getId() << "';";
         
    std::string temp = strm.str();
    std::cout << "DATA_MANAGER - Query UpdateUser: " << temp << std::endl;

    char *query = &temp[0];
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "DATA_MANAGER - SQL error: %s\n", zErrMsg);
        return DATA_ERROR_INSERT_TB;
    } else {
        std::cout << "DATA_MANAGER - Update User successfully" << std::endl;
    }
    return DATA_SUCCESS;
}

ResponseCode DataManager::DeleteUser(User &user) {
    /* "CREATE TABLE USER   ("                                           \
            "ID             INTEGER         PRIMARY KEY AUTOINCREMENT   NOT NULL,"  \
            "EMAIL          NVARCHAR(50)                                NOT NULL,"  \
            "USERNAME       NVARCHER(20)                                NOT NULL,"  \
            "ADDRESS        NVARCHAR(100)                               NOT NULL,"  \
            "PHONE_NUMBER   NVARCHAR(15)                                NOT NULL,"  \
            "FULL_NAME      NVARCHAR(50)                                NOT NULL,"  \
            "PASSWORD       NVARCHAR(20)                                NOT NULL,"  \
            "ROLE           INTEGER                                     NOT NULL);" */
    std::stringstream strm;
    strm << "DELETE FROM USER "
         << "WHERE ID = '" << user.getId() << "';";
         
    std::string temp = strm.str();
    std::cout << "DATA_MANAGER - Query DeleteUser: " << temp << std::endl;

    char *query = &temp[0];
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "DATA_MANAGER - SQL error: %s\n", zErrMsg);
        return DATA_ERROR_INSERT_TB;
    } else {
        std::cout << "DATA_MANAGER - Delete User successfully" << std::endl;
    }
    return DATA_SUCCESS;
}

// Tracking
ResponseCode DataManager::InsertTracking(Tracking &tracking) {
    /* "CREATE TABLE TRACKING  (" \
            "ID                 INTEGER         PRIMARY KEY AUTOINCREMENT   NOT NULL,"              \       
            "LATITUDE           NVARCHAR(20)                                NOT NULL,"              \
            "LONGITUDE          NVARCHAR(20)                                NOT NULL,"              */
    std::stringstream strm;
    strm << "INSERT INTO TRACKING (LATITUDE, LONGITUDE) values ('"
         << tracking.getLatitude()
         << "','" << tracking.getLongititu()
         << "');";
         
    std::string temp = strm.str();
    std::cout << "DATA_MANAGER - Query Insert Tracking: " << temp << std::endl;

    char *query = &temp[0];
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "DATA_MANAGER - SQL error: %s\n", zErrMsg);
        return DATA_ERROR_INSERT_TB;
    } else {
        std::cout << "DATA_MANAGER - Insert Tracking successfully" << std::endl;
    }
    return DATA_SUCCESS;
}
