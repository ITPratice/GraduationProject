#include <string>
#include <stdio.h>
#include <sys/stat.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <cstring>
#include <sqlite3.h>

#include "../ResponseInterface.h"
#include "user.h"
#include "location.h"
#include "user_location.h"

class DataManager {
public:
    DataManager();
    DataManager(std::string pathFile);
    ~DataManager();
public:
    ResponseCode connectDb();
    ResponseCode disconnectDb();

    // User manager
    ResponseCode InsertUser(User &user);
    ResponseCode UpdateUser(User &user);
    ResponseCode DeleteUser(User &user);
    ResponseCode GetAllUser(std::vector<User> &lstUser);

    // Location manager
    ResponseCode InsertLocation(Location &location);
    ResponseCode UpdateLocation(Location &location);
    ResponseCode DeleteLocation(Location &location);

    // User_Location manager
    ResponseCode InsertUserLocation(UserLocation &ul);
    ResponseCode UpdateUserLocation(UserLocation &ul);
    ResponseCode DeleteUserLocation(UserLocation &ul);

public:
    void setDbPath(std::string pathFile);
private:
    sqlite3 *db;
    std::string db_file_path;
    bool isConnect;
private:
    ResponseCode createDb();
    bool dbIsExist();
};
