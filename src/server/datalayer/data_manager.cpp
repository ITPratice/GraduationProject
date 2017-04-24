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
    sql = (char *)"CREATE TABLE VEHICLE    ("                                       \
            "NUMBER_PLATE       NVARCHAR(10)    PRIMARY KEY             NOT NULL,"  \
            "BRANCH_ID          INTEGER                                 NOT NULL,"  \
            "HARDWARE_ID        NVARCHAR(10)                                    ,"  \
            "DESCRIPTION        NVARCHAR(100)                                   ,"  \
            "TYPE_ID            INTEGER                                 NOT NULL,"  \
            "FOREIGN KEY (BRANCH_ID)    REFERENCES BRANCH(ID)           ON DELETE CASCADE "
            "FOREIGN KEY (TYPE_ID)      REFERENCES VEHICLE_TYPE(ID)     ON DELETE CASCADE);";
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
            "FOREIGN KEY (USER_ID)                  REFERENCES USER(ID)                 ON DELETE CASCADE    "  \
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
            "START_DATE                         NVARCHER(10)                                "           \
            "START_TIME                         NVARCHAR(10)                                "           \
            "END_DATE                           NVARCHAR(10)                                "           \
            "END_TIME                           NVARCHAR(10)                                "           \
            "PRIMARY KEY (VEHICLE_NUMBER_PLATE, LOCATION_ID)"                                           \
            "FOREIGN KEY (VEHICLE_NUMBER_PLATE) REFERENCES VEHICLE(NUMBER_PLATE)    ON DELETE CASCADE " \
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
            "ID             INTEGER         PRIMARY KEY AUTOINCREMENT   NOT NULL"   \
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

// User manager
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
    strm << "UPDATE USER SET "
         << "EMAIL = '" << user.getEmail() << "',"
         << "USERNAME = '" << user.getUsername() << "',"
         << "ADDRESS = '" << user.getAddress() << "',"
         << "PHONE_NUMBER = '" << user.getPhoneNumber() << "',"
         << "FULL_NAME = '" << user.getFullname() << "',"
         << "PASSWORD = '" << user.getPassword() << "',"
         << "ROLE = '" << user.getRole() << " "
         << "WHERE ID = '" << user.getId() << "';";
         
    std::string temp = strm.str();
    std::cout << "DATA_MANAGER - Query UpdateUser: " << temp << std::endl;

    char *query = &temp[0];
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "DATA_MANAGER - SQL error: %s\n", zErrMsg);
        return DATA_ERROR_UPDATE_DB;
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
        return DATA_ERROR_DELETE_DB;
    } else {
        std::cout << "DATA_MANAGER - Delete User successfully" << std::endl;
    }
    return DATA_SUCCESS;
}

// VehicleType manager
ResponseCode DataManager::InsertVehicleType(VehicleType &vehicle_type) {
    /*"CREATE TABLE VEHICLE_TYPE    ("                                  \
        "ID             INTEGER         PRIMARY KEY AUTOINCREMENT   NOT NULL,"  \
        "NAME           NVARCHAR(10)                                NOT NULL);"; */
    std::stringstream strm;
    strm << "INSERT INTO VEHICLE_TYPE (NAME) values ('"
         << vehicle_type.getName()
         << "');";
         
    std::string temp = strm.str();
    std::cout << "DATA_MANAGER - Query InsertVehicleType: " << temp << std::endl;

    char *query = &temp[0];
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "DATA_MANAGER - SQL error: %s\n", zErrMsg);
        return DATA_ERROR_INSERT_TB;
    } else {
        std::cout << "DATA_MANAGER - Insert VehicleType successfully" << std::endl;
    }
    return DATA_SUCCESS;
}

ResponseCode DataManager::UpdateVehicleType(VehicleType &vehicle_type) {
    /*"CREATE TABLE VEHICLE_TYPE    ("                                  \
        "ID             INTEGER         PRIMARY KEY AUTOINCREMENT   NOT NULL,"  \
        "NAME           NVARCHAR(10)                                NOT NULL);"; */
    std::stringstream strm;
    strm << "UPDATE VEHICLE_TYPE SET "
         << "NAME = '" << vehicle_type.getName() << "' "
         << "WHERE ID = '" << vehicle_type.getId() << "';";
         
    std::string temp = strm.str();
    std::cout << "DATA_MANAGER - Query UpdateVehicleType: " << temp << std::endl;

    char *query = &temp[0];
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "DATA_MANAGER - SQL error: %s\n", zErrMsg);
        return DATA_ERROR_UPDATE_DB;
    } else {
        std::cout << "DATA_MANAGER - Update VehicleType successfully" << std::endl;
    }
    return DATA_SUCCESS;
}

ResponseCode DataManager::DeleteVehicleType(VehicleType &vehicle_type) {
    /*"CREATE TABLE VEHICLE_TYPE    ("                                  \
        "ID             INTEGER         PRIMARY KEY AUTOINCREMENT   NOT NULL,"  \
        "NAME           NVARCHAR(10)                                NOT NULL);"; */
    std::stringstream strm;
    strm << "DELETE FROM VEHICLE_TYPE "
         << "WHERE ID = '" << vehicle_type.getId() << "';";
         
    std::string temp = strm.str();
    std::cout << "DATA_MANAGER - Query DeleteVehicleType: " << temp << std::endl;

    char *query = &temp[0];
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "DATA_MANAGER - SQL error: %s\n", zErrMsg);
        return DATA_ERROR_DELETE_DB;
    } else {
        std::cout << "DATA_MANAGER - Delete VehicleType successfully" << std::endl;
    }
    return DATA_SUCCESS;
}

// Vehicle manager
ResponseCode DataManager::InsertVehicle(Vehicle &vehicle) {
    /*"CREATE TABLE VEHICLE    ("                                   \
            "NUMBER_PLATE       NVARCHAR(10)    PRIMARY KEY         NOT NULL,"  \
            "BRANCH_ID          INTEGER                             NOT NULL,"  \
            "HARDWARE_ID        NVARCHAR(10)                                ,"  \
            "DESCRIPTION        NVARCHAR(100)                               ,"  \
            "TYPE_ID            INTEGER                             NOT NULL,"  \
            "FOREIGN KEY (TYPE_ID)   REFERENCES VEHICLE_TYPE(ID)    ON DELETE CASCADE);";*/
    std::stringstream strm;
    strm << "INSERT INTO VEHICLE (NUMBER_PLATE, BRANCH_ID, HARDWARE_ID, DESCRIPTION, TYPE_ID) values ('"
         << vehicle.getNumberPlate()
         << "','" << vehicle.getBranchId()
         << "','" << vehicle.getHardwareId()
         << "','" << vehicle.getDescription()
         << "','" << vehicle.getTypeId()
         << "');";
         
    std::string temp = strm.str();
    std::cout << "DATA_MANAGER - Query InsertVehicle: " << temp << std::endl;

    char *query = &temp[0];
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "DATA_MANAGER - SQL error: %s\n", zErrMsg);
        return DATA_ERROR_INSERT_TB;
    } else {
        std::cout << "DATA_MANAGER - Insert Vehicle successfully" << std::endl;
    }
    return DATA_SUCCESS;
}

ResponseCode DataManager::UpdateVehicle(Vehicle &vehicle) {
    /*"CREATE TABLE VEHICLE    ("                                   \
            "NUMBER_PLATE       NVARCHAR(10)    PRIMARY KEY         NOT NULL,"  \
            "BRANCH_ID          INTEGER                             NOT NULL,"  \
            "HARDWARE_ID        NVARCHAR(10)                                ,"  \
            "DESCRIPTION        NVARCHAR(100)                               ,"  \
            "TYPE_ID            INTEGER                             NOT NULL,"  \
            "FOREIGN KEY (TYPE_ID)   REFERENCES VEHICLE_TYPE(ID)    ON DELETE CASCADE);";*/
    std::stringstream strm;
    strm << "UPDATE VEHICLE SET "
         << "BRANCH_ID = '" << vehicle.getBranchId() << "', "
         << "HARDWARE_ID = '" << vehicle.getHardwareId() << "', "
         << "DESCRIPTION = '" << vehicle.getDescription() << "', "
         << "TYPE_ID = '" << vehicle.getTypeId() << "' "
         << "WHERE NUMBER_PLATE = '" << vehicle.getNumberPlate() << "';";
         
    std::string temp = strm.str();
    std::cout << "DATA_MANAGER - Query UpdateVehicle: " << temp << std::endl;

    char *query = &temp[0];
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "DATA_MANAGER - SQL error: %s\n", zErrMsg);
        return DATA_ERROR_UPDATE_DB;
    } else {
        std::cout << "DATA_MANAGER - Update Vehicle successfully" << std::endl;
    }
    return DATA_SUCCESS;
}

ResponseCode DataManager::DeleteVehicle(Vehicle &vehicle) {
     /*"CREATE TABLE VEHICLE    ("                                   \
            "NUMBER_PLATE       NVARCHAR(10)    PRIMARY KEY         NOT NULL,"  \
            "BRANCH_ID          INTEGER                             NOT NULL,"  \
            "HARDWARE_ID        NVARCHAR(10)                                ,"  \
            "DESCRIPTION        NVARCHAR(100)                               ,"  \
            "TYPE_ID            INTEGER                             NOT NULL,"  \
            "FOREIGN KEY (TYPE_ID)   REFERENCES VEHICLE_TYPE(ID)    ON DELETE CASCADE);";*/
    std::stringstream strm;
    strm << "DELETE FROM VEHICLE "
         << "WHERE NUMBER_PLATE = '" << vehicle.getNumberPlate() << "';";
         
    std::string temp = strm.str();
    std::cout << "DATA_MANAGER - Query DeleteVehicle: " << temp << std::endl;

    char *query = &temp[0];
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "DATA_MANAGER - SQL error: %s\n", zErrMsg);
        return DATA_ERROR_DELETE_DB;
    } else {
        std::cout << "DATA_MANAGER - Delete Vehicle successfully" << std::endl;
    }
    return DATA_SUCCESS;
}

// Branch manager
ResponseCode DataManager::InsertBranch(Branch &branch) {
    /*"CREATE TABLE BRANCH("\
        "ID             INTEGER         PRIMARY KEY AUTOINCREMENT   NOT NULL"   \
        "NAME           NVARCHAR(50)                                NOT NULL);"; */
    std::stringstream strm;
    strm << "INSERT INTO BRANCH (NAME) values ('"
         << branch.getName()
         << "');";
         
    std::string temp = strm.str();
    std::cout << "DATA_MANAGER - Query Insert Branch: " << temp << std::endl;

    char *query = &temp[0];
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "DATA_MANAGER - SQL error: %s\n", zErrMsg);
        return DATA_ERROR_INSERT_TB;
    } else {
        std::cout << "DATA_MANAGER - Insert Branch successfully" << std::endl;
    }
    return DATA_SUCCESS;
}

ResponseCode DataManager::UpdateBranch(Branch &branch) {
    /*"CREATE TABLE BRANCH("\
        "ID             INTEGER         PRIMARY KEY AUTOINCREMENT   NOT NULL"   \
        "NAME           NVARCHAR(50)                                NOT NULL);"; */
    std::stringstream strm;
    strm << "UPDATE BRANCH SET "
         << "NAME = '" << branch.getName() << "' "
         << "WHERE ID = " << branch.getId() << "';";
         
    std::string temp = strm.str();
    std::cout << "DATA_MANAGER - Query Update Branch: " << temp << std::endl;

    char *query = &temp[0];
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "DATA_MANAGER - SQL error: %s\n", zErrMsg);
        return DATA_ERROR_UPDATE_DB;
    } else {
        std::cout << "DATA_MANAGER - Update Branch successfully" << std::endl;
    }
    return DATA_SUCCESS;
}

ResponseCode DataManager::DeleteBranch(Branch &branch) {
    /*"CREATE TABLE BRANCH("\
        "ID             INTEGER         PRIMARY KEY AUTOINCREMENT   NOT NULL"   \
        "NAME           NVARCHAR(50)                                NOT NULL);"; */
    std::stringstream strm;
    strm << "DELETE FROM BRANCH "
         << "WHERE ID = " << branch.getId() << "';";
         
    std::string temp = strm.str();
    std::cout << "DATA_MANAGER - Query Delete Branch: " << temp << std::endl;

    char *query = &temp[0];
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "DATA_MANAGER - SQL error: %s\n", zErrMsg);
        return DATA_ERROR_DELETE_DB;
    } else {
        std::cout << "DATA_MANAGER - Delete Branch successfully" << std::endl;
    }
    return DATA_SUCCESS;
}

// UserVehicle manager
ResponseCode DataManager::InsertUserVehicle(UserVehicle &user_vehicle) {
    /*"CREATE TABLE USER_VEHICLE  (" \
        "USER_ID                                INTEGER                             NOT NULL            ,"  \ 
        "VEHICLE_NUMBER_PLATE                   NVARCHAR(10)                        NOT NULL            ,"  \ 
        "PRIMARY KEY (USER_ID, VEHICLE_NUMBER_PLATE)                                                    ,"  \ 
        "FOREIGN KEY (USER_ID)                  REFERENCES USER(ID)                 ON DELETE CASCADE    "  \
        "FOREIGN KEY (VEHICLE_NUMBER_PLATE)     REFERENCES VEHICLE(NUMBER_PLATE)    ON DELETE CASCADE)  ;";*/
    std::stringstream strm;
    strm << "INSERT INTO USER_VEHICLE (USER_ID, VEHICLE_NUMBER_PLATE) values ('"
         << user_vehicle.getUserId()
         << "','" << user_vehicle.getNumberPlate()
         << "');";
         
    std::string temp = strm.str();
    std::cout << "DATA_MANAGER - Query Insert UserVehicle: " << temp << std::endl;

    char *query = &temp[0];
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "DATA_MANAGER - SQL error: %s\n", zErrMsg);
        return DATA_ERROR_INSERT_TB;
    } else {
        std::cout << "DATA_MANAGER - Insert UserVehicle successfully" << std::endl;
    }
    return DATA_SUCCESS;
}

ResponseCode DataManager::UpdateUserVehicle(UserVehicle &user_vehicle) {
    /*"CREATE TABLE USER_VEHICLE  (" \
        "USER_ID                                INTEGER                             NOT NULL            ,"  \ 
        "VEHICLE_NUMBER_PLATE                   NVARCHAR(10)                        NOT NULL            ,"  \ 
        "PRIMARY KEY (USER_ID, VEHICLE_NUMBER_PLATE)                                                    ,"  \ 
        "FOREIGN KEY (USER_ID)                  REFERENCES USER(ID)                 ON DELETE CASCADE    "  \
        "FOREIGN KEY (VEHICLE_NUMBER_PLATE)     REFERENCES VEHICLE(NUMBER_PLATE)    ON DELETE CASCADE)  ;";*/
    return DATA_SUCCESS;
}

ResponseCode DataManager::DeleteUserVehicle(UserVehicle &user_vehicle) {
    /*"CREATE TABLE USER_VEHICLE  (" \
        "USER_ID                                INTEGER                             NOT NULL            ,"  \ 
        "VEHICLE_NUMBER_PLATE                   NVARCHAR(10)                        NOT NULL            ,"  \ 
        "PRIMARY KEY (USER_ID, VEHICLE_NUMBER_PLATE)                                                    ,"  \ 
        "FOREIGN KEY (USER_ID)                  REFERENCES USER(ID)                 ON DELETE CASCADE    "  \
        "FOREIGN KEY (VEHICLE_NUMBER_PLATE)     REFERENCES VEHICLE(NUMBER_PLATE)    ON DELETE CASCADE)  ;";*/
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

ResponseCode DataManager::UpdateTracking(Tracking &tracking) {
    /* "CREATE TABLE TRACKING  (" \
            "ID                 INTEGER         PRIMARY KEY AUTOINCREMENT   NOT NULL,"              \       
            "LATITUDE           NVARCHAR(20)                                NOT NULL,"              \
            "LONGITUDE          NVARCHAR(20)                                NOT NULL,"              */
    std::stringstream strm;
    strm << "UPDATE TRACKING SET "
         << "LATITUDE = '" tracking.getLatitude() << "',"
         << "LONGITUDE = '" << tracking.getLongititu() << "' "
         << "WHERE ID = '" << tracking.getId() << "';";
         
    std::string temp = strm.str();
    std::cout << "DATA_MANAGER - Query Update Tracking: " << temp << std::endl;

    char *query = &temp[0];
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "DATA_MANAGER - SQL error: %s\n", zErrMsg);
        return DATA_ERROR_UPDATE_DB;
    } else {
        std::cout << "DATA_MANAGER - Update Tracking successfully" << std::endl;
    }
    return DATA_SUCCESS;
}

ResponseCode DataManager::DeleteTracking(Tracking &tracking) {
    /* "CREATE TABLE TRACKING  (" \
        "ID                 INTEGER         PRIMARY KEY AUTOINCREMENT   NOT NULL,"              \       
        "LATITUDE           NVARCHAR(20)                                NOT NULL,"              \
        "LONGITUDE          NVARCHAR(20)                                NOT NULL,"              */
    std::stringstream strm;
    strm << "DELETE FROM TRACKING "
         << "WHERE ID = '" << tracking.getId() << "';";
         
    std::string temp = strm.str();
    std::cout << "DATA_MANAGER - Query Delete Tracking: " << temp << std::endl;

    char *query = &temp[0];
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "DATA_MANAGER - SQL error: %s\n", zErrMsg);
        return DATA_ERROR_UPDATE_DB;
    } else {
        std::cout << "DATA_MANAGER - Delete Tracking successfully" << std::endl;
    }
    return DATA_SUCCESS;
}

// Route manager
ResponseCode DataManager::InsertRoute(Route &route) {
    /*"CREATE TABLE ROUTE ("\
        "VEHICLE_NUMBER_PLATE               NVARCHAR(10)                        NOT NULL"           \
        "LOCATION_ID                        INTEGER                             NOT NULL"           \
        "START_DATE                         NVARCHER(10)                                "           \
        "START_TIME                         NVARCHAR(10)                                "           \
        "END_DATE                           NVARCHAR(10)                                "           \
        "END_TIME                           NVARCHAR(10)                                "           \
        "PRIMARY KEY (VEHICLE_NUMBER_PLATE, LOCATION_ID)"                                           \
        "FOREIGN KEY (VEHICLE_NUMBER_PLATE) REFERENCES VEHICLE(NUMBER_PLATE)    ON DELETE CASCADE " \
        "FOREIGN KEY (LOCATION_ID)          REFERENCES  TRACKING(ID)            ON DELETE CASCADE);"; */
    std::stringstream strm;
    strm << "INSERT INTO ROUTE (VEHICLE_NUMBER_PLATE, LOCATION_ID, START_DATE, START_TIME, END_DATE, END_TIME) values ('"
         << route.getNumberPlate()
         << "', '" << route.getLocationId()
         << "', '" << route.getStartDate()
         << "', '" << route.getStartTime()
         << "', '" << route.getEndDate()
         << "', '" << route.getEndTime()         
         << "');";
         
    std::string temp = strm.str();
    std::cout << "DATA_MANAGER - Query Insert Route: " << temp << std::endl;

    char *query = &temp[0];
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "DATA_MANAGER - SQL error: %s\n", zErrMsg);
        return DATA_ERROR_INSERT_TB;
    } else {
        std::cout << "DATA_MANAGER - Insert Route successfully" << std::endl;
    }
    return DATA_SUCCESS;
}

ResponseCode DataManager::UpdateRoute(Route &route) {
    /*"CREATE TABLE ROUTE ("\
        "VEHICLE_NUMBER_PLATE               NVARCHAR(10)                        NOT NULL"           \
        "LOCATION_ID                        INTEGER                             NOT NULL"           \
        "START_DATE                         NVARCHER(10)                                "           \
        "START_TIME                         NVARCHAR(10)                                "           \
        "END_DATE                           NVARCHAR(10)                                "           \
        "END_TIME                           NVARCHAR(10)                                "           \
        "PRIMARY KEY (VEHICLE_NUMBER_PLATE, LOCATION_ID)"                                           \
        "FOREIGN KEY (VEHICLE_NUMBER_PLATE) REFERENCES VEHICLE(NUMBER_PLATE)    ON DELETE CASCADE " \
        "FOREIGN KEY (LOCATION_ID)          REFERENCES  TRACKING(ID)            ON DELETE CASCADE);"; */
    std::stringstream strm;
    strm << "UPDATE ROUTE SET "
         << "VEHICLE_NUMBER_PLATE = '" <<  << "', "
         << "LOCATION_ID = '" <<  << "', "
         << "START_DATE '" << route.getStartDate() << "', "
         << "START_TIME = '" << route.getStartTime() << "', "
         << "END_DATE = '" << route.getEndDate() << "', "
         << "END_TIME = '" << route.getEndTime() << "' "
         << "WHERE VEHICLE_NUMBER_PLATE = '" << route.getNumberPlate() << "' AND "
         << "LOCATION_ID = '" << route.getLocationId() << "';";
         
    std::string temp = strm.str();
    std::cout << "DATA_MANAGER - Query Update Route: " << temp << std::endl;

    char *query = &temp[0];
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "DATA_MANAGER - SQL error: %s\n", zErrMsg);
        return DATA_ERROR_UPDATE_DB;
    } else {
        std::cout << "DATA_MANAGER - Update Route successfully" << std::endl;
    }
    return DATA_SUCCESS;
}