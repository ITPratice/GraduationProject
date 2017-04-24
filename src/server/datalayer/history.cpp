#include "route.h"

History::History() {
    number_plate = "";
    location_id = 1;
    date = "";
    start_time = "";
    end_time = "";
}

History::History(std::string _nPalte, int _location_id, std::string _date, std::string _sTime, std::string _eTime) {
    number_plate = _nPalte;
    location_id = _location_id;
    date = _date;
    start_time = _sTime;
    end_time = _eTime;
}

History::~History() {}

void History::setNumberPlate(std::string _nPlate) {
    number_plate = _nPlate;
}

std::string History::getNumberPlate() {
    return number_plate;
}

void History::setLocationId(int _location_id) {
    location_id = _location_id;
}

int History::getLocationId() {
    return location_id;
}

void History::setDate(std::string _date) {
    date = _date;
}
std::string History::getDate() {
    return date;
}

void History::setStartTime(std::string _sTime) {
    start_time = _sTime;
}

std::string History::getStartTime() {
    return start_time;
}

void History::setEndTime(std::string _eTime) {
    end_time = _eTime;
}

std::string History::getEndTime() {
    return end_time;
}
