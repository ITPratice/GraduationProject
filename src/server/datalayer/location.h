#ifndef LOCATION_H
#define LOCATION_H

#include <string>

class Location {
public:
    Location();
    Location(std::string _lat, std::string _lon, std::string _nPlate);
    ~Location();
private:
    int id;
    std::string latitude;
    std::string longititu;
    std::string number_plate;
public:
    int getId();

    void setLatitude(std::string _lat);
    std::string getLatitude();

    void setLongititu(std::string _lon);
    std::string getLongititu();

    void setNumberPlate(std::string _nPlate);
    std::string getNumberPlate();
};

#endif  // LOCATION_H