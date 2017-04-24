#include "location.h"

Location::Location() {   
    latitude = "";
    longititu = "";
    number_plate = "";
 }

Location::Location(std::string _lat, std::string _lon, std::string _nPlate) {
    latitude = _lat;
    longititu = _lon;
    number_plate = _nPlate;
}

Location::~Location() { }

int Location::getId() {
    return id;
}

void Location::setLatitude(std::string _lat) {
     latitude = _lat;
}

std::string Location::getLatitude() {
     return latitude;
}

void Location::setLongititu(std::string _lon) {
     longititu = _lon;
}

std::string Location::getLongititu() {
     return longititu;
}

void Location::setNumberPlate(std::string _nPlate) {
    number_plate = _nPlate;
}

std::string Location::getNumberPlate() {
    return number_plate;
}

