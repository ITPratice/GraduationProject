#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

class Vehicle {
public:
    Vehicle();
    Vehicle(std::string _nPlate, int _branch_id, std::string _hId, std::string _des, int _tId);
    ~Vehicle();
private:
    std::string number_plate;
    int branch_id;
    std::string hardware_id;
    std::string description;
    int type_id;
public:
    void setNumberPlate(std::string _nPlate);
    std::string getNumberPlate();

    void setBranchId(int _branch_id);
    int getBranchId();

    void setHardwareId(std::string _hId);
    std::string getHardwareId();

    void setDescription(std::string _Des);
    std::string getDescription();

    void setTypeId(int _tId);
    int getTypeId();
};

#endif  // VEHICLE_H