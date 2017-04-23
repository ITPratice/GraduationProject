#include "vehicle_type.h"

VehicleType::VehicleType() {
    name = "";
}

VehicleType::VehicleType(std::string _name) {
    name = _name;
}

VehicleType::~VehicleType() { }

void VehicleType::setName(std::string _name) {
    name = _name;
}

std::string VehicleType::getName() {
    return name;
}