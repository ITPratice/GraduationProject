#include "tracking.h"

Tracking::Tracking() {   
    date = "";
    time = "";
    latitude = "";
    longititu = "";
    hardware_id = "";
 }

Tracking::Tracking(std::string _date, std::string _time, std::string _lat, std::string _lon, std::string _hId) {
    date = _date;
    time = _time;
    latitude = _lat;
    longititu = _lon;
    hardware_id = _hId;
}

Tracking::~Tracking() { }

 void Tracking::setDate(std::string _date) {
     date = _date;
}

std::string Tracking::getDate() {
     return date;
}

void Tracking::setTime(std::string _time) {
     time = _time;
}

std::string Tracking::getTime() {
     return time;
}

void Tracking::setLatitude(std::string _lat) {
     latitude = _lat;
}

std::string Tracking::getLatitude() {
     return latitude;
}

void Tracking::setLongititu(std::string _lon) {
     longititu = _lon;
}

std::string Tracking::getLongititu() {
     return longititu;
}

void Tracking::setHardwareId(std::string _hId) {
    hardware_id = _hId;
}

std::string Tracking::getHardwareId() {
    return hardware_id;
}
