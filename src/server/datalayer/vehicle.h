#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

class Vehicle {
public:
    Vehicle();
    Vehicle(std::string _nPlate, std::string _branch, std::string _color, std::string _hId, std::string _des, int _tId);
    ~Vehicle();
private:
    std::string number_plate;
    std::string branch;
    std::string color;
    std::string hardware_id;
    std::string description;
    int type_id;
public:
    void setNumberPlate(std::string _nPlate);
    std::string getNumberPlate();

    void setBranch(std::string _branch);
    std::string getBranch();

    void setColor(std::string _color);
    std::string getColor();

    void setHardwareId(std::string _hId);
    std::string getHardwareId();

    void setDescription(std::string _Des);
    std::string getDescription();

    void setTypeId(int _tId);
    int getTypeId();
};

#endif  // VEHICLE_H