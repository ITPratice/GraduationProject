#include "route.h"

Route::Route() {
    number_plate = "";
    location_id = 1;
    start_date = "";
    start_time = "";
    end_date = "";
    end_time = "";
}

Route::Route(std::string _nPalte, int _location_id, std::string _sDate, std::string _sTime, std::string _eDate, std::string _eTime) {
    number_plate = _nPalte;
    location_id = _location_id;
    start_date = _sDate;
    start_time = _sTime;
    end_date = _eDate;
    end_time = _eTime;
}

Route::~Route() {}

void Route::setNumberPlate(std::string _nPlate) {
    number_plate = _nPlate;
}

std::string Route::getNumberPlate() {
    return number_plate;
}

void Route::setLocationId(int _location_id) {
    location_id = _location_id;
}

int Route::getLocationId() {
    return location_id;
}

void Route::setStartDate(std::string _sDate) {
    start_date = _sDate;
}
std::string Route::getStartDate() {
    return start_date;
}

void Route::setStartTime(std::string _sTime) {
    start_time = _sTime;
}

std::string Route::getStartTime() {
    return start_time;
}

void Route::setEndDate(std::string _eDate) {
    end_date = _eDate;
}

std::string Route::getEndDate() {
    return end_date;
}

void Route::setEndTime(std::string _eTime) {
    end_time = _eTime;
}

std::string Route::getEndTime() {
    return end_time;
}
