#ifndef USER_VEHICLE_H
#define USER_VEHICLE_H

#include <string>

class UserVehicle {
public:
    UserVehicle();
    UserVehicle(int _uId, std::string _nPlate);
    ~UserVehicle();
private:
    int user_id;
    std::string number_plate;
public:
    void setUserId(int _uId);
    int getUserId();

    void setNumberPlate(std::string _nPlate);
    std::string getNumberPlate();
};

#endif  // USER_VEHICLE_H  