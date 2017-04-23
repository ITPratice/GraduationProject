#include "vehicle.h"

 Vehicle::Vehicle() {
    number_plate = "";
    branch_id = 1;
    hardware_id = "";
    description = "";
    type_id = 1;
 }
    
Vehicle::Vehicle(std::string _nPlate, int _branch_id, std::string _hId, std::string _des, int _tId) {
    number_plate = _nPlate;
    branch_id = _branch_id;
    hardware_id = _hId;
    description = _des;
    type_id = _tId;
}

Vehicle::~Vehicle() { }

void Vehicle::setNumberPlate(std::string _nPlate) {
    number_plate = _nPlate;
}

std::string Vehicle::getNumberPlate() {
    return number_plate;
}

void Vehicle::setBranchId(int _branch_id) {
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

void Vehicle::setTypeId(int _tId) {
    type_id = _tId;
}

int Vehicle::getTypeId() {
    return type_id;
}