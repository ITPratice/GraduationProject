#include "vehicle_type.h"

VehicleType::VehicleType() {
    name = "";
    description = "";
}

VehicleType::VehicleType(std::string _name, std::string _description) {
    name = _name;
    description = _description;
}

VehicleType::~VehicleType() { }

void VehicleType::setName(std::string _name) {
    name = _name;
}

std::string VehicleType::getName() {
    return name;
}

void VehicleType::setDescription(std::string _des) {
    description = _des;
}

std::string VehicleType::getDescription() {
    return description;
}