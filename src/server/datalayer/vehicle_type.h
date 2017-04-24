#ifndef VEHICLE_TYPE_H
#define VEHICLE_TYPE_H

#include <iostream>
#include <string>

class VehicleType {
public:
    VehicleType();
    VehicleType(std::string _name);
    ~VehicleType();
private:
   int id;
    std::string name;
public:
    int getId();

    void setName(std::string _name);
    std::string getName();
};

#endif  // VEHICLE_TYPE_H