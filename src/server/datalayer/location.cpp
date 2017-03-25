#include "location.h"

Location::Location() {
    id = "";
    lat_point = "";
    lon_point = "";
}

Location::Location(std::string _id, std::string _lat, std::string _lon) {
    id = _id;
    lat_point = _lat;
    lon_point = _lon;
}

Location::~Location() {

}

void Location::setId(std::string _id) {
    id = _id;
}

std::string Location::getId() const {
    return id;
}

void Location::setLatPoint(std::string _latPoint) {
    lat_point = _latPoint;
}

std::string Location::getLatPoint() const {
    return lat_point;
}

void Location::setLonPoint(std::string _lonPoint) {
    lon_point = _lonPoint;
}

std::string Location::getLonPoint() const {
    return lon_point;
}
