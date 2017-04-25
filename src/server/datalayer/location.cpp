#include "location.h"

Location::Location() {   
    latitude = "";
    longititu = "";
    number_plate = "";
 }

Location::Location(std::string _lat, std::string _lon, std::string _nPlate, std::string _date, std::string _sTime, std::string _eTime) {
    latitude = _lat;
    longititu = _lon;
    number_plate = _nPlate;
    date = _date;
    start_time = _sTime;
    end_time = _eTime;
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

void Location::setDate(std::string _date) {
    date = _date;
}
std::string Location::getDate() {
    return date;
}

void Location::setStartTime(std::string _sTime) {
    start_time = _sTime;
}

std::string Location::getStartTime() {
    return start_time;
}

void Location::setEndTime(std::string _eTime) {
    end_time = _eTime;
}

std::string Location::getEndTime() {
    return end_time;
}

