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
            "ROLE           INTEGER                                     NOT NULL,"  \
            "IS_FIRST       INTEGER                                     NOT NULL);";    // Updated 03/05/2017
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return DATA_ERROR_CREATE_TB;
    } else {
        fprintf(stdout, "DATA_MANAGER - Table USER created successfully\n");
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
    sql = (char *)"CREATE TABLE BRANCH ("\
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
            "IS_DELETED         INTEGER                                 NOT NULL,"  \
            "WRITE_HISTORY      INTEGER                                 NOT NULL);";
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
            "ID                         INTEGER         PRIMARY KEY AUTOINCREMENT           NOT NULL," \
            "LATITUDE                   VARCHAR(20)                                         NOT NULL," \
            "LONGITUDE                  VARCHAR(20)                                         NOT NULL," \
            "VEHICLE_NUMBER_PLATE       VARCHAR(20)                                         NOT NULL," \
            "DATE                       VARCHER(20)                                                 ," \
            "START_TIME                 VARCHAR(20)                                                 ," \
            "END_TIME                   VARCHAR(20)                                                 ," \
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

// BUG
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

ResponseCode DataManager::Login(std::string email, std::string password) {
    std::stringstream strm;
    strm << "SELECT * FROM USER WHERE EMAIL = '" << email 
         << "' AND PASSWORD = '" << password 
         << "' AND ROLE != 5; ";
    std::string s = strm.str();
    char *str = &s[0];
    sqlite3_stmt *statement;
    char *query = str;
    std::cout << "Login query: " << query << std::endl;
    if(sqlite3_prepare(db, query, -1, &statement, 0) == SQLITE_OK) {
        // int ctotal = sqlite3_column_count(statement);
        int res;
        while (true) {
            res = sqlite3_step(statement);
            if (res == SQLITE_ROW) {
                break;
            } 
            return DATA_ERROR_SELECT_DB;
        }
        sqlite3_finalize(statement);
    } else {
        return DATA_ERROR_SELECT_DB;
    }
    return DATA_SUCCESS;
}


ResponseCode DataManager::LoginAdmin(std::string email, std::string password) {
    std::stringstream strm;
    strm << "SELECT * FROM USER WHERE EMAIL = '" << email 
         << "' AND PASSWORD = '" << password 
         << "' AND ROLE = 1;";
    std::string s = strm.str();
    char *str = &s[0];
    sqlite3_stmt *statement;
    char *query = str;
    std::cout << "LoginAdmin query: " << query << std::endl;

    if(sqlite3_prepare(db, query, -1, &statement, 0) == SQLITE_OK) {
        // int ctotal = sqlite3_column_count(statement);
        int res;
        while(true) {
            res = sqlite3_step(statement);
            if (res == SQLITE_ROW) {
                break;
            } 
            return DATA_ERROR_SELECT_DB;
        }
        sqlite3_finalize(statement);
    } else {
        return DATA_ERROR_SELECT_DB;
    }
    return DATA_SUCCESS;
}

// User manager - Test OK
ResponseCode DataManager::InsertUser(User &user) {
    std::stringstream strm;
    strm << "INSERT INTO USER (EMAIL, USERNAME, ADDRESS, PHONE_NUMBER, FULL_NAME, PASSWORD, ROLE, IS_FIRST) values ('"
         << user.getEmail()
         << "','" << user.getUsername()
         << "','" << user.getAddress()
         << "','" << user.getPhoneNumber()
         << "','" << user.getFullname()
         << "','" << user.getPassword()
         << "','" << user.getRole()
         << "','" << user.getFirst()
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
    std::stringstream strm;
    strm << "UPDATE USER SET "
         << "USERNAME = '" << user.getUsername() << "',"
         << "ADDRESS = '" << user.getAddress() << "',"
         << "PHONE_NUMBER = '" << user.getPhoneNumber() << "',"
         << "FULL_NAME = '" << user.getFullname() << "',"
         << "PASSWORD = '" << user.getPassword() << "',"
         << "ROLE = " << user.getRole() << ","
         << "IS_FIRST = " << user.getFirst() << " "
         << "WHERE EMAIL = '" << user.getEmail() << "'";
         
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

ResponseCode DataManager::DeActiveUser(std::string email) {
    std::stringstream strm;
    strm << "UPDATE USER SET ROLE = 5 "
         << "WHERE EMAIL = '" << email << "';";
         
    std::string temp = strm.str();
    std::cout << "DATA_MANAGER - Query BanUser: " << temp << std::endl;

    char *query = &temp[0];
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "DATA_MANAGER - SQL error: %s\n", zErrMsg);
        return DATA_ERROR_UPDATE_DB;
    } else {
        std::cout << "DATA_MANAGER - Ban User successfully" << std::endl;
    }
    return DATA_SUCCESS;
}

ResponseCode DataManager::ChangePassIfFirst(std::string newPass, std::string email) {
    User _user;
    if(GetUserByEmail(email, _user) == DATA_SUCCESS) {
        if(_user.getFirst() == 1) {
            std::stringstream strm;
            strm << "UPDATE USER SET "
                 << "PASSWORD = '" << newPass << "', "
                 << "IS_FIRST = 0 "
                 << "WHERE EMAIL = '" << email << "';";
         
            std::string temp = strm.str();
            std::cout << "DATA_MANAGER - Query IsFirstChangePass: " << temp << std::endl;

            char *query = &temp[0];
            char *zErrMsg = 0;
            int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
            if(rc != SQLITE_OK) {
                fprintf(stderr, "DATA_MANAGER - SQL error: %s\n", zErrMsg);
                return DATA_ERROR_UPDATE_DB;
            } else {
                std::cout << "DATA_MANAGER - IsFirstChangePass successfully" << std::endl;
                return DATA_SUCCESS;
            }
        } else {
            return DATA_ERROR_SELECT_DB;
        }
    } else {
        return DATA_ERROR_SELECT_DB;
    }
}

ResponseCode DataManager::ActiveUser(std::string email) {
    User _user;
    if(GetUserByEmail(email, _user) == DATA_SUCCESS) {
        if(_user.getRole() == 2) {
            std::stringstream strm;
            strm << "UPDATE USER SET ROLE = 3 "
                 << "WHERE EMAIL = '" << email << "';";
         
            std::string temp = strm.str();
            std::cout << "DATA_MANAGER - Query ActiveUser: " << temp << std::endl;

            char *query = &temp[0];
            char *zErrMsg = 0;
            int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
            if(rc != SQLITE_OK) {
                fprintf(stderr, "DATA_MANAGER - SQL error: %s\n", zErrMsg);
                return DATA_ERROR_UPDATE_DB;
            } else {
                std::cout << "DATA_MANAGER - ActiveUser successfully" << std::endl;
                return DATA_SUCCESS;
            }
        } else {
            return DATA_ERROR_SELECT_DB;
        }
    } else {
        return DATA_ERROR_SELECT_DB;
    }
}

// VehicleType manager - Test OK
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

// Vehicle manager - Test OK
ResponseCode DataManager::InsertVehicle(Vehicle &vehicle) {
    std::stringstream strm;
    strm << "INSERT INTO VEHICLE (NUMBER_PLATE, BRANCH_ID, HARDWARE_ID, DESCRIPTION, TYPE_ID, USER_EMAIL, IS_DELETED, WRITE_HISTORY) values ('"
         << vehicle.getNumberPlate()
         << "', '" << vehicle.getBranchId()
         << "', '" << vehicle.getHardwareId()
         << "', '" << vehicle.getDescription()
         << "', '" << vehicle.getTypeId()
         << "', '" << vehicle.getUserEmail()
         << "',  " << vehicle.getDeleted()
         << ",   " << vehicle.getWriteHistory()
         << ");";
         
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
    std::stringstream strm;
    strm << "UPDATE VEHICLE SET "
         << "BRANCH_ID = '" << vehicle.getBranchId() << "', "
         << "HARDWARE_ID = '" << vehicle.getHardwareId() << "', "
         << "DESCRIPTION = '" << vehicle.getDescription() << "', "
         << "TYPE_ID = '" << vehicle.getTypeId() << "', "
         << "USER_EMAIL = '" << vehicle.getUserEmail() << "', "
         << "IS_DELETED = " << vehicle.getDeleted() << ", "
         << "WRITE_HISTORY = " << vehicle.getWriteHistory() << " "
         << "WHERE NUMBER_PLATE = '" << vehicle.getNumberPlate() << "'";
         
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
    std::stringstream strm;
    strm << "UPDATE FROM VEHICLE "
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

ResponseCode DataManager::BanVehicle(std::string nPlate) {
    std::stringstream strm;
    strm << "UPDATE VEHICLE SET IS_DELETED = 1 "
         << "WHERE NUMBER_PLATE = '" << nPlate << "';";
         
    std::string temp = strm.str();
    std::cout << "DATA_MANAGER - Query BanVehicle: " << temp << std::endl;

    char *query = &temp[0];
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "DATA_MANAGER - SQL error: %s\n", zErrMsg);
        return DATA_ERROR_UPDATE_DB;
    } else {
        std::cout << "DATA_MANAGER - BanVehicle successfully" << std::endl;
    }
    return DATA_SUCCESS;
}

ResponseCode DataManager::UpdateWriteHistory(std::string nPlate) {
    std::stringstream strm;
    strm << "UPDATE VEHICLE SET WRITE_HISTORY = 1 "
         << "WHERE NUMBER_PLATE = '" << nPlate << "';";
         
    std::string temp = strm.str();
    std::cout << "DATA_MANAGER - Query Update History: " << temp << std::endl;

    char *query = &temp[0];
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "DATA_MANAGER - SQL error: %s\n", zErrMsg);
        return DATA_ERROR_UPDATE_DB;
    } else {
        std::cout << "DATA_MANAGER - BanVehicle successfully" << std::endl;
    }
    return DATA_SUCCESS;
}

ResponseCode DataManager::GetWriteHistory(std::string nPlate, int &wHistory) {
    std::stringstream strm;
    strm << "SELECT WRITE_HISTORY FROM VEHICLE "
         << "WHERE NUMBER_PLATE = '" << nPlate << "';";

    std::string temp = strm.str();
    std::cout << "DATA_MANAGER - Query Update History: " << temp << std::endl;

    char *query = &temp[0];
    sqlite3_stmt *stmt;
    if(sqlite3_prepare(db, query, -1, &stmt, 0) == SQLITE_OK) {
        int res = 0;
        while (true) {
            res = sqlite3_step(stmt);

            if (res == SQLITE_ROW) {
                wHistory = atoi((char*)sqlite3_column_text(stmt, 0));
            }

            if ( res == SQLITE_DONE || res == SQLITE_ERROR) {
                break;
            }
        }
        sqlite3_finalize(stmt);
    } else {
        return DATA_ERROR_SELECT_DB;
    }
    return DATA_SUCCESS;
}

// Branch manager - Test OK
ResponseCode DataManager::InsertBranch(Branch &branch) {
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
    std::stringstream strm;
    strm << "UPDATE BRANCH SET "
         << "NAME = '" << branch.getName() << "' "
         << "WHERE ID = '" << branch.getId() << "';";
         
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
    std::stringstream strm;
    strm << "DELETE FROM BRANCH "
         << "WHERE ID = '" << branch.getId() << "';";
         
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

// Location - Test OK
ResponseCode DataManager::InsertLocation(Location &location) {
    std::stringstream strm;
    strm << "INSERT INTO LOCATION (LATITUDE, LONGITUDE, VEHICLE_NUMBER_PLATE, DATE, START_TIME, END_TIME) values ('"
         << location.getLatitude()
         << "', '" << location.getLongititu()
         << "', '" << location.getNumberPlate()
         << "', '" << location.getDate()
         << "', '" << location.getStartTime()
         << "', '" << location.getEndTime()
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
    std::stringstream strm;
    strm << "UPDATE LOCATION SET "
         << "LATITUDE = '" << location.getLatitude() << "',"
         << "LONGITUDE = '" << location.getLongititu() << "', "
         << "VEHICLE_NUMBER_PLATE = '" << location.getNumberPlate() << "' "
         << "DATE = '" << location.getDate() << "' "
         << "START_TIME = '" << location.getStartTime() << "' "
         << "END_TIME = '" << location.getEndTime() << "' "
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

// Get User by Id
ResponseCode DataManager::GetUserByEmail(std::string email, User &outUser) {
    std::stringstream strm;
    strm << "SELECT * FROM USER WHERE EMAIL = '" << email << "';";
    std::string s = strm.str();
	char *str = &s[0];
	sqlite3_stmt *statement;
	char *query = str;
    std::cout << "GetUserByEmail query: " << query << std::endl;

    if (sqlite3_prepare(db, query, -1, &statement, 0) == SQLITE_OK) {
		int res = 0;
		res = sqlite3_step(statement);
		if (res == SQLITE_ROW) {
            outUser.setEmail((char*)sqlite3_column_text(statement, 0));
            outUser.setUsername((char*)sqlite3_column_text(statement, 1));
            outUser.setAddress((char*)sqlite3_column_text(statement, 2));
            outUser.setPhoneNumber((char*)sqlite3_column_text(statement, 3));
            outUser.setFullname((char*)sqlite3_column_text(statement, 4));
            outUser.setPassword((char*)sqlite3_column_text(statement, 5));
            outUser.setRole(atoi((char*)sqlite3_column_text(statement, 6)));
            outUser.setFirst(atoi((char*)sqlite3_column_text(statement, 7)));
		} else {
            return DATA_SELECT_EMPTY;
		}
		sqlite3_finalize(statement);
	} else {
		return DATA_ERROR_SELECT_DB;
	}
	return DATA_SUCCESS;
}

ResponseCode DataManager::GetAllUser(std::vector<User>& lstUser) {
    sqlite3_stmt *stmt;
    const char* query = (char *)"SELECT * FROM USER;";
    std::cout << "GetAllUser query: " << query << std::endl;
    if(sqlite3_prepare(db, query, -1, &stmt, 0) == SQLITE_OK) {
        int res = 0;
        while (true) {
            res = sqlite3_step(stmt);

            if (res == SQLITE_ROW) {
                User user;
                user.setEmail((char*)sqlite3_column_text(stmt, 0));
                user.setUsername((char*)sqlite3_column_text(stmt, 1));
                user.setAddress((char*)sqlite3_column_text(stmt, 2));
                user.setPhoneNumber((char*)sqlite3_column_text(stmt, 3));
                user.setFullname((char*)sqlite3_column_text(stmt, 4));
                user.setPassword((char*)sqlite3_column_text(stmt, 5));
                user.setRole(atoi((char*)sqlite3_column_text(stmt, 6)));
                user.setFirst(atoi((char*)sqlite3_column_text(stmt, 7)));
                lstUser.push_back(user);
            }

            if ( res == SQLITE_DONE || res == SQLITE_ERROR) {
                break;
            }
        }
        sqlite3_finalize(stmt);
    } else {
        return DATA_ERROR_SELECT_DB;
    }
    return DATA_SUCCESS;
}

ResponseCode DataManager::GetAllUserWaiting(std::vector<User>& lstUser) {
    sqlite3_stmt *stmt;
    const char* query = (char *)"SELECT * FROM USER WHERE ROLE = 2;";

    std::cout << "GetAllUserWaiting query: " << query << std::endl;

    if(sqlite3_prepare(db, query, -1, &stmt, 0) == SQLITE_OK) {
        int res = 0;
        while (true) {
            res = sqlite3_step(stmt);

            if (res == SQLITE_ROW) {
                User user;
                user.setEmail((char*)sqlite3_column_text(stmt, 0));
                user.setUsername((char*)sqlite3_column_text(stmt, 1));
                user.setAddress((char*)sqlite3_column_text(stmt, 2));
                user.setPhoneNumber((char*)sqlite3_column_text(stmt, 3));
                user.setFullname((char*)sqlite3_column_text(stmt, 4));
                user.setPassword((char*)sqlite3_column_text(stmt, 5));
                user.setRole(atoi((char*)sqlite3_column_text(stmt, 6)));
                user.setFirst(atoi((char*)sqlite3_column_text(stmt, 7)));
                lstUser.push_back(user);
            }

            if ( res == SQLITE_DONE || res == SQLITE_ERROR) {
                break;
            }
        }
        sqlite3_finalize(stmt);
    } else {
        return DATA_ERROR_SELECT_DB;
    }
    return DATA_SUCCESS;
}

ResponseCode DataManager::GetBranchById(std::string id, Branch &outBranch) {
    std::stringstream strm;
    strm << "SELECT * FROM BRANCH WHERE ID = '" << id << "';";

    std::string s = strm.str();
	char *str = &s[0];
	sqlite3_stmt *statement;
	char *query = str;

    std::cout << "GetBranchById query: " << query << std::endl;

    if (sqlite3_prepare(db, query, -1, &statement, 0) == SQLITE_OK) {
		int res = 0;
		res = sqlite3_step(statement);
		if (res == SQLITE_ROW) {
            outBranch.setId((char*)sqlite3_column_text(statement, 0));
            outBranch.setName((char*)sqlite3_column_text(statement, 1));
		} else {
            return DATA_SELECT_EMPTY;
		}
		sqlite3_finalize(statement);
	} else {
		return DATA_ERROR_SELECT_DB;
	}
	return DATA_SUCCESS;
}

ResponseCode DataManager::GetVehicleByNumberPlate(std::string nPlate, Vehicle &outVehicle) {
    std::stringstream strm;
    strm << "SELECT * FROM VEHICLE WHERE NUMBER_PLATE = '" << nPlate << "';";

    std::string s = strm.str();
	char *str = &s[0];
	sqlite3_stmt *statement;
	char *query = str;

    std::cout << "GetVehicleByNumberPlate query: " << query << std::endl;

    if (sqlite3_prepare(db, query, -1, &statement, 0) == SQLITE_OK) {
		int res = 0;
		res = sqlite3_step(statement);
		if (res == SQLITE_ROW) {
            outVehicle.setNumberPlate((char*)sqlite3_column_text(statement, 0));
            outVehicle.setBranchId((char*)sqlite3_column_text(statement, 1));
            outVehicle.setHardwareId((char*)sqlite3_column_text(statement, 2));
            outVehicle.setDescription((char*)sqlite3_column_text(statement, 3));
            outVehicle.setTypeId((char*)sqlite3_column_text(statement, 4));
            outVehicle.setUserEmail((char*)sqlite3_column_text(statement, 5));
            outVehicle.setDeleted(atoi((char*)sqlite3_column_text(statement, 6)));
            outVehicle.setWriteHistory(atoi((char*)sqlite3_column_text(statement, 7)));
		} else {
            return DATA_SELECT_EMPTY;
		}
		sqlite3_finalize(statement);
	} else {
		return DATA_ERROR_SELECT_DB;
	}
	return DATA_SUCCESS;
} 

ResponseCode DataManager::GetVehicleTypeById(std::string id, VehicleType &outVehicleType) {
    std::stringstream strm;
    strm << "SELECT * FROM VEHICLE_TYPE WHERE ID = '" << id << "';";

    std::string s = strm.str();
	char *str = &s[0];
	sqlite3_stmt *statement;
	char *query = str;

    std::cout << "GetVehicleTypeById query: " << query << std::endl;

    if (sqlite3_prepare(db, query, -1, &statement, 0) == SQLITE_OK) {
		int res = 0;
		res = sqlite3_step(statement);
		if (res == SQLITE_ROW) {
            outVehicleType.setId((char*)sqlite3_column_text(statement, 0));
            outVehicleType.setName((char*)sqlite3_column_text(statement, 1));
		} else {
            return DATA_SELECT_EMPTY;
		}
		sqlite3_finalize(statement);
	} else {
		return DATA_ERROR_SELECT_DB;
	}
	return DATA_SUCCESS;
}

ResponseCode DataManager::GetLocationByDate(std::string plate, std::string date, std::vector<Location> &outLocation) {
    std::stringstream strm;
    strm << "SELECT * FROM LOCATION WHERE VEHICLE_NUMBER_PLATE = '" 
         << plate 
         << "' AND [DATE] = '" 
         << date << "' AND START_TIME != \"\";";

    std::string s = strm.str();
	char *str = &s[0];
	sqlite3_stmt *stmt;
	char *query = str;

    std::cout << "GetLocationByDate query: " << query << std::endl;
    
    if (sqlite3_prepare(db, query, -1, &stmt, 0) == SQLITE_OK) {
        int res = 0;
        while (true) {
            res = sqlite3_step(stmt);
            if (res == SQLITE_ROW) {
                Location _location;
                _location.setLatitude((char*)sqlite3_column_text(stmt, 1));
                _location.setLongititu((char*)sqlite3_column_text(stmt, 2));
                _location.setNumberPlate((char*)sqlite3_column_text(stmt, 3));
                _location.setDate((char*)sqlite3_column_text(stmt, 4));
                _location.setStartTime((char*)sqlite3_column_text(stmt, 5));
                _location.setEndTime((char*)sqlite3_column_text(stmt, 6));
                outLocation.push_back(_location);
            }

            if ( res == SQLITE_DONE || res == SQLITE_ERROR) {
                break;
            }
        }
        sqlite3_finalize(stmt);
    } else {
        return DATA_ERROR_SELECT_DB;
    }
    return DATA_SUCCESS;
}

ResponseCode DataManager::GetCurrentLocation(std::string nPlate, Location &outLocation) {
    std::stringstream strm;
    strm << "SELECT * FROM LOCATION WHERE VEHICLE_NUMBER_PLATE = '" 
         << nPlate 
         << "' ORDER BY ID DESC LIMIT 1;" ;

    std::string s = strm.str();
	char *str = &s[0];
	sqlite3_stmt *stmt;
	char *query = str;

    std::cout << "GetCurrentLocation query: " << query << std::endl;
    
    if (sqlite3_prepare(db, query, -1, &stmt, 0) == SQLITE_OK) {
        int res = 0;
        res = sqlite3_step(stmt);
        if (res == SQLITE_ROW) {
            outLocation.setLatitude((char*)sqlite3_column_text(stmt, 1));
            outLocation.setLongititu((char*)sqlite3_column_text(stmt, 2));
            outLocation.setNumberPlate((char*)sqlite3_column_text(stmt, 3));
            outLocation.setDate((char*)sqlite3_column_text(stmt, 4));
            outLocation.setStartTime((char*)sqlite3_column_text(stmt, 5));
            outLocation.setEndTime((char*)sqlite3_column_text(stmt, 6));
        }

        if (res == SQLITE_DONE || res == SQLITE_ERROR) {
            return DATA_ERROR_SELECT_DB;
        }
        sqlite3_finalize(stmt);
    } else {
        return DATA_ERROR_SELECT_DB;
    }
    return DATA_SUCCESS;
}

ResponseCode DataManager::GetVehicleNumberByUser(std::string email, std::vector<std::string> &outVehicleNumber) {
    std::stringstream strm;
    strm << "SELECT NUMBER_PLATE FROM VEHICLE WHERE USER_EMAIL = '" << email << "';";
    std::string s = strm.str();
    std::cout << "Query: " << s << std::endl;
	char *str = &s[0];
	sqlite3_stmt *statement;
	char *query = str;

    std::cout << "GetVehicleNumberByUser query: " << query << std::endl;

    if (sqlite3_prepare(db, query, -1, &statement, 0) == SQLITE_OK) {
        while (true) {
            int res = 0;
            res = sqlite3_step(statement);

            if (res == SQLITE_ROW) {
                outVehicleNumber.push_back((char*)sqlite3_column_text(statement, 0));
            }

            if ( res == SQLITE_DONE || res == SQLITE_ERROR) {
                break;
            }
        }
        sqlite3_finalize(statement);
	} else {
		return DATA_ERROR_SELECT_DB;
	}
	return DATA_SUCCESS;
}

ResponseCode DataManager::GetAllVehicleType(std::vector<VehicleType> &lstVehicleType) {
    sqlite3_stmt *stmt;
    const char* query = (char *)"SELECT * FROM VEHICLE_TYPE;";
    std::cout << "GetAllVehicleType query: " << query << std::endl;
    if(sqlite3_prepare(db, query, -1, &stmt, 0) == SQLITE_OK) {
        int res = 0;
        while (true) {
            res = sqlite3_step(stmt);

            if (res == SQLITE_ROW) {
                VehicleType _vehicleType;
                _vehicleType.setId((char*)sqlite3_column_text(stmt, 0));
                _vehicleType.setName((char*)sqlite3_column_text(stmt, 1));
                lstVehicleType.push_back(_vehicleType);
            }

            if ( res == SQLITE_DONE || res == SQLITE_ERROR) {
                break;
            }
        }
        sqlite3_finalize(stmt);
    } else {
        return DATA_ERROR_SELECT_DB;
    }
    return DATA_SUCCESS;
}

ResponseCode DataManager::GetAllVehicle(std::vector<Vehicle> &lstVehicle) {
    sqlite3_stmt *stmt;
    const char* query = (char *)"SELECT * FROM VEHICLE;";
    std::cout << "GetAllVehicle query: " << query << std::endl;
    if(sqlite3_prepare(db, query, -1, &stmt, 0) == SQLITE_OK) {
        int res = 0;
        while (true) {
            res = sqlite3_step(stmt);

            if (res == SQLITE_ROW) {
                Vehicle _vehicle;
                _vehicle.setNumberPlate((char*)sqlite3_column_text(stmt, 0));
                _vehicle.setBranchId((char*)sqlite3_column_text(stmt, 1));
                _vehicle.setHardwareId((char*)sqlite3_column_text(stmt, 2));
                _vehicle.setDescription((char*)sqlite3_column_text(stmt, 3));
                _vehicle.setTypeId((char*)sqlite3_column_text(stmt, 4));
                _vehicle.setUserEmail((char*)sqlite3_column_text(stmt, 5));
                _vehicle.setDeleted(atoi((char*)sqlite3_column_text(stmt, 6)));
                _vehicle.setWriteHistory(atoi((char*)sqlite3_column_text(stmt, 7)));
                lstVehicle.push_back(_vehicle);
            }

            if ( res == SQLITE_DONE || res == SQLITE_ERROR) {
                break;
            }
        }
        sqlite3_finalize(stmt);
    } else {
        return DATA_ERROR_SELECT_DB;
    }
    return DATA_SUCCESS;
}

ResponseCode DataManager::GetAllBranch(std::vector<Branch> &lstBranch) {
    sqlite3_stmt *stmt;
    const char* query = (char *)"SELECT * FROM BRANCH;";
    std::cout << "GetAllBranch query: " << query << std::endl;
    if(sqlite3_prepare(db, query, -1, &stmt, 0) == SQLITE_OK) {
        int res = 0;
        while (true) {
            res = sqlite3_step(stmt);

            if (res == SQLITE_ROW) {
                Branch _branch;
                _branch.setId((char*)sqlite3_column_text(stmt, 0));
                _branch.setName((char*)sqlite3_column_text(stmt, 1));
                lstBranch.push_back(_branch);
            }

            if ( res == SQLITE_DONE || res == SQLITE_ERROR) {
                break;
            }
        }
        sqlite3_finalize(stmt);
    } else {
        return DATA_ERROR_SELECT_DB;
    }
    return DATA_SUCCESS;
}
