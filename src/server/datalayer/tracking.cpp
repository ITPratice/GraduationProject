#include "tracking.h"

Tracking::Tracking() {   
    latitude = "";
    longititu = "";
 }

Tracking::Tracking(std::string _lat, std::string _lon) {
    latitude = _lat;
    longititu = _lon;
}

Tracking::~Tracking() { }

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
