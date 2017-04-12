#include "vehicle.h"

 Vehicle::Vehicle() {
    number_plate = "";
    branch = "";
    color = "";
    hardware_id = "";
    description = "";
    type_id = 0;
 }
    
Vehicle::Vehicle(std::string _nPlate, std::string _branch, std::string _color, std::string _hId, std::string _des, int _tId) {
    number_plate = _nPlate;
    branch = _branch;
    color = _color;
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

void Vehicle::setBranch(std::string _branch) {
    branch = _branch;
}

std::string Vehicle::getBranch() {
    return branch;
}

void Vehicle::setColor(std::string _color) {
    color = _color;
}

std::string Vehicle::getColor() {
    return color;
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