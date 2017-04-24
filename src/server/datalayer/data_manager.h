#include <string>
#include <stdio.h>
#include <sys/stat.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <cstring>
#include <sqlite3.h>
#include <ctime>

#include "../ResponseInterface.h"

#include "user.h"
#include "tracking.h"
#include "vehicle_type.h"
#include "vehicle.h"
#include "branch.h"
#include "user_vehicle.h"
#include "route.h"

#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

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
    ResponseCode Login(std::string email, std::string password);
    ResponseCode GetAllUser(std::vector<User>& lstUser);

    // VehicleType manager
    ResponseCode InsertVehicleType(VehicleType &vehicle_type);
    ResponseCode UpdateVehicleType(VehicleType &vehicle_type);
    ResponseCode DeleteVehicleType(VehicleType &vehicle_type);

    // Vehicle manager
    ResponseCode InsertVehicle(Vehicle &vehicle);
    ResponseCode UpdateVehicle(Vehicle &vehicle);
    ResponseCode DeleteVehicle(Vehicle &vehicle);

    // Branch manager
    ResponseCode InsertBranch(Branch &branch);
    ResponseCode UpdateBranch(Branch &branch);
    ResponseCode DeleteBranch(Branch &branch);

    // UserVehicle manager
    ResponseCode InsertUserVehicle(UserVehicle &user_vehicle);
    ResponseCode UpdateUserVehicle(UserVehicle &user_vehicle);
    ResponseCode DeleteUserVehicle(UserVehicle &user_vehicle);

    // Tracking manager
    ResponseCode InsertTracking(Tracking &tracking);
    ResponseCode UpdateTracking(Tracking &tracking);
    ResponseCode DeleteTracking(Tracking &tracking);

    // Route manager
    ResponseCode InsertRoute(Route &route);
    ResponseCode UpdateRoute(Route &route);

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

#endif
