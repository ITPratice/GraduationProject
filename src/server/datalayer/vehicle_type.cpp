#include "vehicle_type.h"

VehicleType::VehicleType() {
    name = "";
    id = "";
}

VehicleType::VehicleType(std::string _id, std::string _name) {
    name = _name;
    id = _id;
}

VehicleType::~VehicleType() { }

void VehicleType::setId(std::string _id) {
    id = _id;
}

std::string VehicleType::getId() {
    return id;
}

void VehicleType::setName(std::string _name) {
    name = _name;
}

std::string VehicleType::getName() {
    return name;
}