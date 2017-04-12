#include "user_vehicle.h"

UserVehicle::UserVehicle() {
    user_id = 0;
    number_plate = "";
}

UserVehicle::UserVehicle(int _uId, std::string _nPlate) {
    user_id = _uId;
    number_plate = _nPlate;
}

UserVehicle::~UserVehicle() { }

void UserVehicle::setUserId(int _uId) {
    user_id = _uId;
}

int UserVehicle::getUserId() {
    return user_id;
}

void UserVehicle::setNumberPlate(std::string _nPlate) {
    number_plate = _nPlate;
}

std::string UserVehicle::getNumberPlate() {
    return number_plate;
}