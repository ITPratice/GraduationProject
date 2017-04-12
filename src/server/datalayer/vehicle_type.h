#ifndef VEHICLE_TYPE_H
#define VEHICLE_TYPE_H

#include <iostream>
#include <string>

class VehicleType {
public:
    VehicleType();
    VehicleType(std::string _name, std::string _description);
    ~VehicleType();
private:
    std::string name;
    std::string description;
public:
    void setName(std::string _name);
    std::string getName();

    void setDescription(std::string _des);
    std::string getDescription();
};

#endif  // VEHICLE_TYPE_H