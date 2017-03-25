#include <iostream>
#include <string>

#ifndef LOCATION_H
#define LOCATION_H

class Location {
public:
    Location();
    Location(std::string _id, std::string _lat, std::string _lon);
    ~Location();
private : 
    std::string id;
    std::string lat_point;
    std::string lon_point;
public:
    void setId(std::string _id);
    std::string getId() const;

    void setLatPoint(std::string _latPoint);
    std::string getLatPoint() const;

    void setLonPoint(std::string _lonPoint);
    std::string getLonPoint() const;
};

#endif  // LOCATION_H
