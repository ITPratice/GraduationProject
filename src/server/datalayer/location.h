#ifndef LOCATION_H
#define LOCATION_H

#include <string>

class Location {
public:
    Location();
    Location(std::string _lat, std::string _lon, std::string _nPlate, std::string _date, std::string _sTime, std::string _eTime);
    ~Location();
private:
    int id;
    std::string latitude;
    std::string longititu;
    std::string number_plate;
    std::string date;
    std::string start_time;
    std::string end_time;
public:
    int getId();

    void setLatitude(std::string _lat);
    std::string getLatitude();

    void setLongititu(std::string _lon);
    std::string getLongititu();

    void setNumberPlate(std::string _nPlate);
    std::string getNumberPlate();

    void setDate(std::string _date);
    std::string getDate();

    void setStartTime(std::string _sTime);
    std::string getStartTime();

    void setEndTime(std::string _eTime);
    std::string getEndTime();
};

#endif  // LOCATION_H