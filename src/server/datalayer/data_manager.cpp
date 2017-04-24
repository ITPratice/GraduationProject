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

    // Create USERS table - OK
    sql = (char *)"CREATE TABLE USER   (" \
            "EMAIL          VARCHAR(80)        PRIMARY KEY              NOT NULL,"  \
            "USERNAME       VARCHER(20)                                 NOT NULL,"  \
            "ADDRESS        NVARCHAR(100)                               NOT NULL,"  \
            "PHONE_NUMBER   VARCHAR(20)                                 NOT NULL,"  \
            "FULL_NAME      NVARCHAR(100)                               NOT NULL,"  \
            "PASSWORD       VARCHAR(20)                                 NOT NULL,"  \
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

    // Cretae Vehicle_type table - OK
    sql = (char *)"CREATE TABLE VEHICLE_TYPE (" \
            "ID             VARCHAR(10)         PRIMARY KEY         NOT NULL,"  \
            "NAME           NVARCHAR(50)                            NOT NULL);";
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return DATA_ERROR_CREATE_TB;
    } else {
        fprintf(stdout, "DATA_MANAGER - Table VEHICLE_TYPE created successfully\n");
    }

    // Create BRANCH table - OK
    sql = (char *)"CREATE TABLE BRANCH("\
            "ID             VARCHAR(10)         PRIMARY KEY             NOT NULL,"   \
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

    // Create VEHICLES table - OK
    sql = (char *)"CREATE TABLE VEHICLE    ("                                       \
            "NUMBER_PLATE       VARCHAR(20)         PRIMARY KEY         NOT NULL,"  \
            "BRANCH_ID          VARCHAR(10)                             NOT NULL,"  \
            "HARDWARE_ID        VARCHAR(10)                             NOT NULL,"  \
            "DESCRIPTION        NVARCHAR(200)                                   ,"  \
            "TYPE_ID            VARCHAR(10)                             NOT NULL,"  \
            "USER_EMAIL         VARCHAR(80)                             NOT NULL,"  \
            "FOREIGN KEY (USER_EMAIL)    REFERENCES USER(EMAIL)         ON DELETE CASCADE "
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

    // Create LOCATION table - OK
    sql = (char *)"CREATE TABLE LOCATION  (" \
            "ID                     INTEGER         PRIMARY KEY AUTOINCREMENT           NOT NULL," \
            "LATITUDE               VARCHAR(20)                                         NOT NULL," \
            "LONGITUDE              VARCHAR(20)                                         NOT NULL," \
            "VEHICLE_NUMBER_PLATE   VARCHAR(20)                                         NOT NULL," \
            "FOREIGN KEY (VEHICLE_NUMBER_PLATE)     REFERENCES VEHICLE(NUMBER_PLATE)    ON DELETE CASCADE);";
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return DATA_ERROR_CREATE_TB;
    } else {
        fprintf(stdout, "DATA_MANAGER - Table LOCATION created successfully\n");
    }

    // Create HISTORY table - OK
    sql = (char *)"CREATE TABLE HISTORY (" \
            "VEHICLE_NUMBER_PLATE               VARCHAR(20)                         NOT NULL,"           \
            "LOCATION_ID                        INTEGER                             NOT NULL,"           \
            "DATE                               VARCHER(20)                                 ,"           \
            "START_TIME                         VARCHAR(20)                                 ,"           \
            "END_TIME                           VARCHAR(20)                                 ,"           \
            "PRIMARY KEY (VEHICLE_NUMBER_PLATE, LOCATION_ID),"                                           \
            "FOREIGN KEY (VEHICLE_NUMBER_PLATE) REFERENCES  VEHICLE(NUMBER_PLATE)   ON DELETE CASCADE " \
            "FOREIGN KEY (LOCATION_ID)          REFERENCES  LOCATION(ID)            ON DELETE CASCADE);";
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return DATA_ERROR_CREATE_TB;
    } else {
        fprintf(stdout, "DATA_MANAGER - Table HISTORY created successfully\n");
    }
    return DATA_SUCCESS;
}

bool DataManager::dbIsExist() {
    std::cout << "DATA_MANAGER - File .db full name: " << db_file_path << std::endl;

    std::stringstream strm;
    strm << "SELECT name FROM sqlite_master WHERE type = 'table' AND name = 'USER';";
    std::string s = strm.str();
    char *str = &s[0];
    sqlite3_stmt *statement;
    char *query = str;

    if (sqlite3_prepare(db, query, -1, &statement, 0) == SQLITE_OK) {
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
    if (!dbIsExist()) {
        std::cout << "DATA_MANAGER - Start create DB\n";
        ResponseCode ret = createDb();
        if (ret != DATA_SUCCESS) {
            return ret;
        }
    }

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
   /* "CREATE TABLE USER   (" \
            "EMAIL          VARCHAR(80)        PRIMARY KEY              NOT NULL,"  \
            "USERNAME       VARCHER(20)                                 NOT NULL,"  \
            "ADDRESS        NVARCHAR(100)                               NOT NULL,"  \
            "PHONE_NUMBER   VARCHAR(20)                                 NOT NULL,"  \
            "FULL_NAME      NVARCHAR(100)                               NOT NULL,"  \
            "PASSWORD       VARCHAR(20)                                 NOT NULL,"  \
            "ROLE           INTEGER                                     NOT NULL);"; */
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
   /* "CREATE TABLE USER   (" \
            "EMAIL          VARCHAR(80)        PRIMARY KEY              NOT NULL,"  \
            "USERNAME       VARCHER(20)                                 NOT NULL,"  \
            "ADDRESS        NVARCHAR(100)                               NOT NULL,"  \
            "PHONE_NUMBER   VARCHAR(20)                                 NOT NULL,"  \
            "FULL_NAME      NVARCHAR(100)                               NOT NULL,"  \
            "PASSWORD       VARCHAR(20)                                 NOT NULL,"  \
            "ROLE           INTEGER                                     NOT NULL);";*/
    std::stringstream strm;
    strm << "UPDATE USER SET "
         << "USERNAME = '" << user.getUsername() << "',"
         << "ADDRESS = '" << user.getAddress() << "',"
         << "PHONE_NUMBER = '" << user.getPhoneNumber() << "',"
         << "FULL_NAME = '" << user.getFullname() << "',"
         << "PASSWORD = '" << user.getPassword() << "',"
         << "ROLE = '" << user.getRole() << " "
         << "WHERE EMAIL = '" << user.getEmail() << "';";
         
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
    /* "CREATE TABLE USER   (" \
            "EMAIL          VARCHAR(80)        PRIMARY KEY              NOT NULL,"  \
            "USERNAME       VARCHER(20)                                 NOT NULL,"  \
            "ADDRESS        NVARCHAR(100)                               NOT NULL,"  \
            "PHONE_NUMBER   VARCHAR(20)                                 NOT NULL,"  \
            "FULL_NAME      NVARCHAR(100)                               NOT NULL,"  \
            "PASSWORD       VARCHAR(20)                                 NOT NULL,"  \
            "ROLE           INTEGER                                     NOT NULL);"; */
    std::stringstream strm;
    strm << "DELETE FROM USER "
         << "WHERE EMAIL = '" << user.getEmail() << "';";
         
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
    /*"CREATE TABLE VEHICLE_TYPE (" \
            "ID             VARCHAR(10)         PRIMARY KEY         NOT NULL,"  \
            "NAME           NVARCHAR(50)                            NOT NULL);"; */
    std::stringstream strm;
    strm << "INSERT INTO VEHICLE_TYPE (ID, NAME) values ('"
         << vehicle_type.getId() << "', '"
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
    /*"CREATE TABLE VEHICLE_TYPE (" \
            "ID             VARCHAR(10)         PRIMARY KEY         NOT NULL,"  \
            "NAME           NVARCHAR(50)                            NOT NULL);"; */
    std::stringstream strm;
    strm << "UPDATE VEHICLE_TYPE SET "
         << "NAME = '" << vehicle_type.getName() << "' "
         << "WHERE ID = '" << vehicle_type.getId() << "';";
         
    std::string temp = strm.str();
    std::cout << "DATA_MANAGER - Query Update VehicleType: " << temp << std::endl;

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
    /*"CREATE TABLE VEHICLE_TYPE (" \
            "ID             VARCHAR(10)         PRIMARY KEY         NOT NULL,"  \
            "NAME           NVARCHAR(50)                            NOT NULL);";  */
    std::stringstream strm;
    strm << "DELETE FROM VEHICLE_TYPE "
         << "WHERE ID = '" << vehicle_type.getId() << "';";
         
    std::string temp = strm.str();
    std::cout << "DATA_MANAGER - Query Delete VehicleType: " << temp << std::endl;

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
    /*"CREATE TABLE VEHICLE    ("                                       \
            "NUMBER_PLATE       VARCHAR(20)         PRIMARY KEY         NOT NULL,"  \
            "BRANCH_ID          VARCHAR(10)                             NOT NULL,"  \
            "HARDWARE_ID        VARCHAR(10)                             NOT NULL,"  \
            "DESCRIPTION        NVARCHAR(200)                                   ,"  \
            "TYPE_ID            VARCHAR(10)                             NOT NULL,"  \
            "USER_EMAIL         VARCHAR(80)                             NOT NULL,"  \
            "FOREIGN KEY (USER_EMAIL)    REFERENCES USER(EMAIL)         ON DELETE CASCADE "
            "FOREIGN KEY (BRANCH_ID)    REFERENCES BRANCH(ID)           ON DELETE CASCADE "
            "FOREIGN KEY (TYPE_ID)      REFERENCES VEHICLE_TYPE(ID)     ON DELETE CASCADE);";*/
    std::stringstream strm;
    strm << "INSERT INTO VEHICLE (NUMBER_PLATE, BRANCH_ID, HARDWARE_ID, DESCRIPTION, TYPE_ID, USER_EMAIL) values ('"
         << vehicle.getNumberPlate()
         << "', '" << vehicle.getBranchId()
         << "', '" << vehicle.getHardwareId()
         << "', '" << vehicle.getDescription()
         << "', '" << vehicle.getTypeId()
         << "', '" << vehicle.getUserEmail()
         << "');";
         
    std::string temp = strm.str();
    std::cout << "DATA_MANAGER - Query Insert Vehicle: " << temp << std::endl;

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
    /*"CREATE TABLE VEHICLE    ("                                       \
            "NUMBER_PLATE       VARCHAR(20)         PRIMARY KEY         NOT NULL,"  \
            "BRANCH_ID          VARCHAR(10)                             NOT NULL,"  \
            "HARDWARE_ID        VARCHAR(10)                             NOT NULL,"  \
            "DESCRIPTION        NVARCHAR(200)                                   ,"  \
            "TYPE_ID            VARCHAR(10)                             NOT NULL,"  \
            "USER_EMAIL         VARCHAR(80)                             NOT NULL,"  \
            "FOREIGN KEY (USER_EMAIL)   REFERENCES USER(EMAIL)         ON DELETE CASCADE "
            "FOREIGN KEY (BRANCH_ID)    REFERENCES BRANCH(ID)           ON DELETE CASCADE "
            "FOREIGN KEY (TYPE_ID)      REFERENCES VEHICLE_TYPE(ID)     ON DELETE CASCADE);";*/
    std::stringstream strm;
    strm << "UPDATE VEHICLE SET "
         << "BRANCH_ID = '" << vehicle.getBranchId() << "', "
         << "HARDWARE_ID = '" << vehicle.getHardwareId() << "', "
         << "DESCRIPTION = '" << vehicle.getDescription() << "', "
         << "TYPE_ID = '" << vehicle.getTypeId() << "', "
         << "USER_EMAIL = '" << vehicle.getUserEmail() << "' "
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
     /*"CREATE TABLE VEHICLE    ("                                       \
            "NUMBER_PLATE       VARCHAR(20)         PRIMARY KEY         NOT NULL,"  \
            "BRANCH_ID          VARCHAR(10)                             NOT NULL,"  \
            "HARDWARE_ID        VARCHAR(10)                             NOT NULL,"  \
            "DESCRIPTION        NVARCHAR(200)                                   ,"  \
            "TYPE_ID            VARCHAR(10)                             NOT NULL,"  \
            "USER_EMAIL         VARCHAR(80)                             NOT NULL,"  \
            "FOREIGN KEY (USER_EMAIL)   REFERENCES USER(EMAIL)         ON DELETE CASCADE "
            "FOREIGN KEY (BRANCH_ID)    REFERENCES BRANCH(ID)           ON DELETE CASCADE "
            "FOREIGN KEY (TYPE_ID)      REFERENCES VEHICLE_TYPE(ID)     ON DELETE CASCADE);";*/
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
            "ID             VARCHAR(10)         PRIMARY KEY             NOT NULL,"   \
            "NAME           NVARCHAR(50)                                NOT NULL);"*/
    std::stringstream strm;
    strm << "INSERT INTO BRANCH (ID, NAME) values ('"
         << branch.getId() << "', '"
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
            "ID             VARCHAR(10)         PRIMARY KEY             NOT NULL,"   \
            "NAME           NVARCHAR(50)                                NOT NULL);" */
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
            "ID             VARCHAR(10)         PRIMARY KEY             NOT NULL,"   \
            "NAME           NVARCHAR(50)                                NOT NULL);"*/
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

// Location
ResponseCode DataManager::InsertLocation(Location &location) {
    /* "CREATE TABLE LOCATION  (" \
            "ID                     INTEGER         PRIMARY KEY AUTOINCREMENT           NOT NULL," \
            "LATITUDE               VARCHAR(20)                                         NOT NULL," \
            "LONGITUDE              VARCHAR(20)                                         NOT NULL," \
            "VEHICLE_NUMBER_PLATE   VARCHAR(20)                                         NOT NULL," \
            "FOREIGN KEY (VEHICLE_NUMBER_PLATE)     REFERENCES VEHICLE(NUMBER_PLATE)    ON DELETE CASCADE);*/
    std::stringstream strm;
    strm << "INSERT INTO LOCATION (LATITUDE, LONGITUDE, VEHICLE_NUMBER_PLATE) values ('"
         << location.getLatitude()
         << "', '" << location.getLongititu()
         << "', '" << location.getNumberPlate()
         << "');";
         
    std::string temp = strm.str();
    std::cout << "DATA_MANAGER - Query Insert Location: " << temp << std::endl;

    char *query = &temp[0];
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "DATA_MANAGER - SQL error: %s\n", zErrMsg);
        return DATA_ERROR_INSERT_TB;
    } else {
        std::cout << "DATA_MANAGER - Insert Location successfully" << std::endl;
    }
    return DATA_SUCCESS;
}

ResponseCode DataManager::UpdateLocation(Location &location) {
    /* "CREATE TABLE LOCATION  (" \
            "ID                     INTEGER         PRIMARY KEY AUTOINCREMENT           NOT NULL," \
            "LATITUDE               VARCHAR(20)                                         NOT NULL," \
            "LONGITUDE              VARCHAR(20)                                         NOT NULL," \
            "VEHICLE_NUMBER_PLATE   VARCHAR(20)                                         NOT NULL," \
            "FOREIGN KEY (VEHICLE_NUMBER_PLATE)     REFERENCES VEHICLE(NUMBER_PLATE)    ON DELETE CASCADE);*/
    std::stringstream strm;
    strm << "UPDATE LOCATION SET "
         << "LATITUDE = '" << location.getLatitude() << "',"
         << "LONGITUDE = '" << location.getLongititu() << "', "
         << "VEHICLE_NUMBER_PLATE = '" << location.getNumberPlate() << "' '"
         << "WHERE ID = '" << location.getId() << "';";
         
    std::string temp = strm.str();
    std::cout << "DATA_MANAGER - Query Update Location: " << temp << std::endl;

    char *query = &temp[0];
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "DATA_MANAGER - SQL error: %s\n", zErrMsg);
        return DATA_ERROR_UPDATE_DB;
    } else {
        std::cout << "DATA_MANAGER - Update Location successfully" << std::endl;
    }
    return DATA_SUCCESS;
}

ResponseCode DataManager::DeleteLocation(Location &location) {
    /* "CREATE TABLE LOCATION  (" \
            "ID                     INTEGER         PRIMARY KEY AUTOINCREMENT           NOT NULL," \
            "LATITUDE               VARCHAR(20)                                         NOT NULL," \
            "LONGITUDE              VARCHAR(20)                                         NOT NULL," \
            "VEHICLE_NUMBER_PLATE   VARCHAR(20)                                         NOT NULL," \
            "FOREIGN KEY (VEHICLE_NUMBER_PLATE)     REFERENCES VEHICLE(NUMBER_PLATE)    ON DELETE CASCADE); */
    std::stringstream strm;
    strm << "DELETE FROM LOCATION "
         << "WHERE ID = '" << location.getId() << "';";
         
    std::string temp = strm.str();
    std::cout << "DATA_MANAGER - Query Delete Location: " << temp << std::endl;

    char *query = &temp[0];
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "DATA_MANAGER - SQL error: %s\n", zErrMsg);
        return DATA_ERROR_UPDATE_DB;
    } else {
        std::cout << "DATA_MANAGER - Delete Location successfully" << std::endl;
    }
    return DATA_SUCCESS;
}

// Route manager
ResponseCode DataManager::InsertHistory(History &history) {
    /*"CREATE TABLE HISTORY (" \
            "VEHICLE_NUMBER_PLATE               VARCHAR(20)                         NOT NULL,"           \
            "LOCATION_ID                        INTEGER                             NOT NULL,"           \
            "DATE                               VARCHER(20)                                 ,"           \
            "START_TIME                         VARCHAR(20)                                 ,"           \
            "END_TIME                           VARCHAR(20)                                 ,"           \
            "PRIMARY KEY (VEHICLE_NUMBER_PLATE, LOCATION_ID),"                                           \
            "FOREIGN KEY (VEHICLE_NUMBER_PLATE) REFERENCES  VEHICLE(NUMBER_PLATE)   ON DELETE CASCADE " \
            "FOREIGN KEY (LOCATION_ID)          REFERENCES  LOCATION(ID)            ON DELETE CASCADE);"*/
    std::stringstream strm;
    strm << "INSERT INTO HISTORY (VEHICLE_NUMBER_PLATE, LOCATION_ID, DATE, START_TIME, END_TIME) values ('"
         << history.getNumberPlate()
         << "', '" << history.getLocationId()
         << "', '" << history.getDate()
         << "', '" << history.getStartTime()
         << "', '" << route.getEndTime()         
         << "');";
         
    std::string temp = strm.str();
    std::cout << "DATA_MANAGER - Query Insert History: " << temp << std::endl;

    char *query = &temp[0];
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "DATA_MANAGER - SQL error: %s\n", zErrMsg);
        return DATA_ERROR_INSERT_TB;
    } else {
        std::cout << "DATA_MANAGER - Insert History successfully" << std::endl;
    }
    return DATA_SUCCESS;
}

ResponseCode DataManager::UpdateHistory(History &history) {
    /*"CREATE TABLE HISTORY (" \
            "VEHICLE_NUMBER_PLATE               VARCHAR(20)                         NOT NULL,"           \
            "LOCATION_ID                        INTEGER                             NOT NULL,"           \
            "DATE                               VARCHER(20)                                 ,"           \
            "START_TIME                         VARCHAR(20)                                 ,"           \
            "END_TIME                           VARCHAR(20)                                 ,"           \
            "PRIMARY KEY (VEHICLE_NUMBER_PLATE, LOCATION_ID),"                                           \
            "FOREIGN KEY (VEHICLE_NUMBER_PLATE) REFERENCES  VEHICLE(NUMBER_PLATE)   ON DELETE CASCADE " \
            "FOREIGN KEY (LOCATION_ID)          REFERENCES  LOCATION(ID)            ON DELETE CASCADE);" */
    std::stringstream strm;
    strm << "UPDATE HISTORY SET "
         << "DATE '" << route.getStartDate() << "', "
         << "START_TIME = '" << route.getStartTime() << "', "
         << "END_TIME = '" << route.getEndTime() << "' "
         << "WHERE VEHICLE_NUMBER_PLATE = '" << route.getNumberPlate() << "' AND "
         << "LOCATION_ID = '" << route.getLocationId() << "';";
         
    std::string temp = strm.str();
    std::cout << "DATA_MANAGER - Query Update History: " << temp << std::endl;

    char *query = &temp[0];
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "DATA_MANAGER - SQL error: %s\n", zErrMsg);
        return DATA_ERROR_UPDATE_DB;
    } else {
        std::cout << "DATA_MANAGER - Update History successfully" << std::endl;
    }
    return DATA_SUCCESS;
}