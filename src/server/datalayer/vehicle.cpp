#include "vehicle.h"

 Vehicle::Vehicle() {
    number_plate = "";
    branch_id = "";
    hardware_id = "";
    description = "";
    type_id = "";
    user_email = "";
 }
    
Vehicle::Vehicle(std::string _nPlate, std::string _branch_id, std::string _hId, std::string _des, std::string _tId, std::string _uEmail) {
    number_plate = _nPlate;
    branch_id = _branch_id;
    hardware_id = _hId;
    description = _des;
    type_id = _tId;
    user_email = _uEmail;
}

Vehicle::~Vehicle() { }

void Vehicle::setNumberPlate(std::string _nPlate) {
    number_plate = _nPlate;
}

std::string Vehicle::getNumberPlate() {
    return number_plate;
}

void Vehicle::setBranchId(std::string _branch_id) {
    branch_id = _branch_id;
}

std::string Vehicle::getBranchId() {
    return branch_id;
}

void Vehicle::setHardwareId(std::string _hId) {
    hardware_id = _hId;
}

std::string Vehicle::getHardwareId() {
    return hardware_id;
}

void Vehicle::setDescription(std::string _des) {
    description = _des;
}

std::string Vehicle::getDescription() {
    return description;
}

void Vehicle::setTypeId(std::string _tId) {
    type_id = _tId;
}

std::string Vehicle::getTypeId() {
    return type_id;
}

void Vehicle::setUserEmail(std::string _uEmail) {
    user_email = _uEmail;
}

std::string Vehicle::getUserEmail() {
    return user_email;
}