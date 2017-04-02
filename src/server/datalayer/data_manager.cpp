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

    sql = "CREATE TABLE USER("                                          \
            "ID             NVARCHAR(10)    PRIMARY KEY     NOT NULL,"  \
            "EMAIL          NVARCHAR(100)                   NOT NULL,"  \
            "ADDRESS        NVARCHAR(100)                   NOT NULL,"  \
            "PHONE_NUMBER   NVARCHAR(100)                   NOT NULL,"  \
            "PASSWORD       NVARCHAR(100)                   NOT NULL,"  \
            "NUMBER_PLATE   NVARCHAR(100)                   NOT NULL,"  \
            "TYPE           INT                             NOT NULL);";
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return DATA_ERROR_CREATE_TB;
    } else {
        fprintf(stdout, "DATA_MANAGER - Table USER created successfully\n");
    }

    sql = "CREATE TABLE LOCATION("                                      \
            "ID             NVARCHAR(10)    PRIMARY KEY     NOT NULL,"  \
            "LAT_POINT      NVARCHAR(20)                    NOT NULL,"  \
            "LON_POINT      NVARCHAR(20)                    NOT NULL);";
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return DATA_ERROR_CREATE_TB;
    } else {
        fprintf(stdout, "DATA_MANAGER - Table LOCATION created successfully\n");
    }

    sql = "CREATE TABLE USER_LOCATION("                                     \
            "USER_ID        NVARCHAR(10)                    NOT NULL,"      \
            "LOCATION_ID    NVARCHAR(10)                    NOT NULL,"      \
            "TIME           NVARCHAR(20)                    NOT NULL,"     \
            "PRIMARY KEY (USER_ID, LOCATION_ID),"                           \
            "FOREIGN KEY (USER_ID) REFERENCES USER(ID) ON DELETE CASCADE,"  \
            "FOREIGN KEY (LOCATION_ID) REFERENCES LOCATION(ID) ON DELETE CASCADE);";
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return DATA_ERROR_CREATE_TB;
    } else {
        fprintf(stdout, "DATA_MANAGER - Table USER_LOCATION created successfully\n");
    }
    return DATA_SUCCESS;
}

bool DataManager::dbIsExist() {
    std::cout << "DATA_MANAGER - File .db full name: " << db_file_path << std::endl;

    char* sql = "SELECT name FROM sqlite_master WHERE type='table' AND name='USER';";

    sqlite3_stmt *statement;
    if (sqlite3_prepare(db, sql, -1, &statement, 0 ) == SQLITE_OK) {
        int res = 0;
        res = sqlite3_step(statement);
        if ( res != SQLITE_ROW ) {
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

    int rc;

    rc = sqlite3_open(db_file_path.c_str(), &db);

    if( rc ){
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

ResponseCode DataManager::InsertUser(User &user) {
     /* "ID             NVARCHAR(10)    PRIMARY KEY     NOT NULL,"  \
        "EMAIL          NVARCHAR(100)                   NOT NULL,"  \
        "ADDRESS        NVARCHAR(100)                   NOT NULL,"  \
        "PHONE_NUMBER   NVARCHAR(100)                   NOT NULL,"  \
        "PASSWORD       NVARCHAR(100)                   NOT NULL,"  \
        "NUMBER_PLATE   NVARCHAR(100)                   NOT NULL,"  \
        "TYPE           INT                             NOT NULL) */
    std::stringstream strm;
    strm << "INSERT INTO USER(ID, EMAIL, ADDRESS, PHONE_NUMBER, PASSWORD, NUMBER_PLATE, TYPE) values ('"
         << user.getId()
         << "','" << user.getEmail()
         << "','" << user.getAddress()
         << "','" << user.getPhoneNumber()
         << "','" << user.getPassword()
         << "','" << user.getNumberPlate()
         << "','" << (int)user.getType()
         << "');";
    std::string temp = strm.str();
    std::cout << "DATA_MANAGER - Query Insert User: " << temp << std::endl;

    char *query = &temp[0];
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "DATA_MANAGER - SQL error: %s\n", zErrMsg);
        return DATA_ERROR_INSERT_TB;
    } else {
        std::cout << "DATA_MANAGER - Insert user " << user.getEmail() << " Successfully" << std::endl;
    }
    return DATA_SUCCESS;
}

ResponseCode DataManager::UpdateUser(User &user) {
    /* "ID             NVARCHAR(10)    PRIMARY KEY     NOT NULL,"  \
       "EMAIL          NVARCHAR(100)                   NOT NULL,"  \
       "ADDRESS        NVARCHAR(100)                   NOT NULL,"  \
       "PHONE_NUMBER   NVARCHAR(100)                   NOT NULL,"  \
       "PASSWORD       NVARCHAR(100)                   NOT NULL,"  \
       "NUMBER_PLATE   NVARCHAR(100)                   NOT NULL,"  \
       "TYPE           INT                             NOT NULL) */
    std::stringstream strm;
    strm << "UPDATE USER SET EMAIL  = '"
         << user.getEmail()
         << "', ADDRESS = '" << user.getAddress()
         << "', PHONE_NUMBER = '" << user.getPhoneNumber()
         << "', PASSWORD = '" << user.getPassword()
         << "', NUMBER_PLATE = '" << user.getNumberPlate()
         << "', TYPE = '" << (int)user.getType()
         << "' WHERE ID = '" << user.getId() << "';";
    std::string temp = strm.str();
    std::cout << "DATA_MANAGER - Query Update User: " << temp << std::endl;

    char *query = &temp[0];
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "DATA_MANAGER - SQL error: %s\n", zErrMsg);
        return DATA_ERROR_UPDATE_DB;
    } else {
        std::cout << "DATA_MANAGER - Update user " << user.getEmail() << " Successfully" << std::endl;
    }
    return DATA_SUCCESS;
}

ResponseCode DataManager::DeleteUser(User &user) {
    /* "ID             NVARCHAR(10)    PRIMARY KEY     NOT NULL,"  \
       "EMAIL          NVARCHAR(100)                   NOT NULL,"  \
       "ADDRESS        NVARCHAR(100)                   NOT NULL,"  \
       "PHONE_NUMBER   NVARCHAR(100)                   NOT NULL,"  \
       "PASSWORD       NVARCHAR(100)                   NOT NULL,"  \
       "NUMBER_PLATE   NVARCHAR(100)                   NOT NULL,"  \
       "TYPE           INT                             NOT NULL) */
    std::stringstream strm;
    strm << "DELETE FROM USER WHERE ID = '" << user.getId() << "';";

    std::string temp = strm.str();
    std::cout << "DATA_MANAGER - Query Delete User: " << temp << std::endl;

    char *query = &temp[0];
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "DATA_MANAGER - SQL error: %s\n", zErrMsg);
        return DATA_ERROR_DELETE_DB;
    } else {
        std::cout << "DATA_MANAGER - Delete user " << user.getEmail() << " Successfully" << std::endl;
    }
    return DATA_SUCCESS;
}

ResponseCode DataManager::InsertLocation(Location &location) {
     /* "ID             NVARCHAR(10)    PRIMARY KEY     NOT NULL,"  \
        "LAT_POINT      NVARCHAR(20)                    NOT NULL,"  \
        "LON_POINT      NVARCHAR(20)                    NOT NULL);" */
    std::stringstream strm;
    strm << "INSERT INTO LOCATION (ID, LAT_POINT, LON_POINT) VALUES ('"
         << location.getId()
         << "','" << location.getLatPoint()
         << "','" << location.getLonPoint()
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
        std::cout << "DATA_MANAGER - Insert Location " << location.getId() << " Successfully" << std::endl;
    }
    return DATA_SUCCESS;
}

ResponseCode DataManager::UpdateLocation(Location &location) {
    /* "ID             NVARCHAR(10)    PRIMARY KEY     NOT NULL,"  \
       "LAT_POINT      NVARCHAR(20)                    NOT NULL,"  \
       "LON_POINT      NVARCHAR(20)                    NOT NULL);" */
    std::stringstream strm;
    strm << "UPDATE LOCATION SET LAT_POINT = " << location.getLatPoint()
         << "', LON_POINT = '" << location.getLonPoint()
         << "'WHERE = '" << location.getId()
         << "';'";

    std::string temp = strm.str();
    std::cout << "DATA_MANAGER - Query Update Location: " << temp << std::endl;

    char *query = &temp[0];
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "DATA_MANAGER - SQL error: %s\n", zErrMsg);
        return DATA_ERROR_UPDATE_DB;
    } else {
        std::cout << "DATA_MANAGER - Update Location " << location.getId() << " Successfully" << std::endl;
    }
    return DATA_SUCCESS;
}

ResponseCode DataManager::DeleteLocation(Location &location) {
    /* "ID             NVARCHAR(10)    PRIMARY KEY     NOT NULL,"  \
       "LAT_POINT      NVARCHAR(20)                    NOT NULL,"  \
       "LON_POINT      NVARCHAR(20)                    NOT NULL);" */
    std::stringstream strm;
    strm << "DELETE FROM LOCATION WHERE ID = '" << location.getId() << "';";

    std::string temp = strm.str();
    std::cout << "DATA_MANAGER - Query Delete Location: " << temp << std::endl;

    char *query = &temp[0];
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "DATA_MANAGER - SQL error: %s\n", zErrMsg);
        return DATA_ERROR_DELETE_DB;
    } else {
        std::cout << "DATA_MANAGER - Delete Location " << location.getId() << " Successfully" << std::endl;
    }
    return DATA_SUCCESS;
}

ResponseCode DataManager::InsertUserLocation(UserLocation &ul) {
    /*"CREATE TABLE USER_LOCATION("                                     \
      "USER_ID        NVARCHAR(10)                    NOT NULL,"      \
      "LOCATION_ID    NVARCHAR(10)                    NOT NULL,"      \
      "TIME           NVARCHAR(20)                    NOT NULL,"     \ */
    std::stringstream strm;
    strm << "INSERT INTO USER_LOCATION (USER_ID, LOCATION_ID, TIME) VALUES '"
         << ul.getUserId()
         << "','" << ul.getLocationId()
         << "','" << ul.getTime()
         << ");'";

    std::string temp = strm.str();
    std::cout << "DATA_MANAGER - Query Inser UserLocation: " << temp << std::endl;

    char *query = &temp[0];
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "DATA_MANAGER - SQL error: %s\n", zErrMsg);
        return DATA_ERROR_INSERT_TB;
    } else {
        std::cout << "DATA_MANAGER - Insert UserLocation " << ul.getUserId() << " Successfully" << std::endl;
    }
    return DATA_SUCCESS;
}

ResponseCode DataManager::UpdateUserLocation(UserLocation &ul) {
    /*"CREATE TABLE USER_LOCATION("                                     \
      "USER_ID        NVARCHAR(10)                    NOT NULL,"      \
      "LOCATION_ID    NVARCHAR(10)                    NOT NULL,"      \
      "TIME           NVARCHAR(20)                    NOT NULL,"     \ */
    std::stringstream strm;
    strm << "UPDATE USER_LOCATION SET TIME = " << ul.getTime()
         << " WHERE USER_ID = '" << ul.getUserId()
         << "' AND LOCATION_ID = '" << ul.getLocationId() << "';'";

    std::string temp = strm.str();
    std::cout << "DATA_MANAGER - Query Update UserLocation: " << temp << std::endl;

    char *query = &temp[0];
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "DATA_MANAGER - SQL error: %s\n", zErrMsg);
        return DATA_ERROR_UPDATE_DB;
    } else {
        std::cout << "DATA_MANAGER - Update UserLocation " << ul.getUserId() << " Successfully" << std::endl;
    }
    return DATA_SUCCESS;
}

ResponseCode DataManager::DeleteUserLocation(UserLocation &ul) {
    /*"CREATE TABLE USER_LOCATION("                                     \
      "USER_ID        NVARCHAR(10)                    NOT NULL,"      \
      "LOCATION_ID    NVARCHAR(10)                    NOT NULL,"      \
      "TIME           NVARCHAR(20)                    NOT NULL,"     \ */
    std::stringstream strm;
    strm << "DELETE FROM USER_LOCATION WHERE USER_ID = '" << ul.getUserId() << "' AND LOCATION_ID = '" << ul.getLocationId() << "';";

    std::string temp = strm.str();
    std::cout << "DATA_MANAGER - Query Delete UserLocation: " << temp << std::endl;

    char *query = &temp[0];
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "DATA_MANAGER - SQL error: %s\n", zErrMsg);
        return DATA_ERROR_DELETE_DB;
    } else {
        std::cout << "DATA_MANAGER - Delete UserLocation " << ul.getUserId() << " Successfully" << std::endl;
    }
    return DATA_SUCCESS;
}
