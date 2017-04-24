#ifndef VEHICLE_TYPE_H
#define VEHICLE_TYPE_H

#include <iostream>
#include <string>

class VehicleType {
public:
    VehicleType();
    VehicleType(std::string _name, std::string _id);
    ~VehicleType();
private:
    std::string id;
    std::string name;
public:
    void setId(std::string _id);
    std::string getId();

    void setName(std::string _name);
    std::string getName();
};

#endif  // VEHICLE_TYPE_H