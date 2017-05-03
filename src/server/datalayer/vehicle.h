#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

class Vehicle {
public:
    Vehicle();
    Vehicle(std::string _nPlate, std::string _branch_id, std::string _hId, std::string _des, std::string _tId, std::string _uEmail, int _deleted);
    ~Vehicle();
private:
    std::string number_plate;
    std::string branch_id;
    std::string hardware_id;
    std::string description;
    std::string type_id;
    std::string user_email;
    int deleted;
public:
    void setNumberPlate(std::string _nPlate);
    std::string getNumberPlate();

    void setBranchId(std::string _branch_id);
    std::string getBranchId();

    void setHardwareId(std::string _hId);
    std::string getHardwareId();

    void setDescription(std::string _Des);
    std::string getDescription();

    void setTypeId(std::string _tId);
    std::string getTypeId();

    void setUserEmail(std::string _uEmail);
    std::string getUserEmail();

    void setDeleted(int _deleted);
    int getDeleted();
};

#endif  // VEHICLE_H