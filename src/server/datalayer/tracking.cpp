#include "tracking.h"

Tracking::Tracking() {
    this.tracking_date = "";
    this.tracking_time = "";
    this.lat_point = "";
    this.lon_point = "";
    this.vehicle_number = "";
    this.hardware_id = "";
 }

 Tracking::Tracking(std::string _date, std::string _time, std::string _lat, std::string _lon, std::string _vNumber, std::string _hId) {
    this.tracking_date = _date;
    this.tracking_time = _time;
    this.lat_point = _lat;
    this.lon_point = _lon;
    this.vehicle_number = _vNumber;
    this.hardware_id = _hId;
 }

 Tracking::~Tracking() { }

 void Tracking::setTrackingDate(std::string _date) {
     this.tracking_date = _date;
 }

 std::string Tracking::getTrackingDate() {
     return tracking_date;
 }

 void Tracking::setTrackingTime(std::string _time) {
     this.tracking_time = _time;
 }

 std::string Tracking::getTrackingTime() {
     return tracking_time;
 }

 void Tracking::setLatPoint(std::string _lat) {
     this.lat_point = _lat;
 }

 std::string Tracking::getLatPoint() {
     return lat_point;
 }

 void Tracking::setLonPoint(std::string _lon) {
     this.lon_point = _lon;
 }

 std::string Tracking::getLonPoint() {
     return lon_point;
 }

 void Tracking::setVehicleNumber(std::string _vNumber) {
     this.vehicle_number = _vNumber;
 }

 std::string Tracking::getVehicleNumber() {
     return vehicle_number;
 }

 void Tracking::setHardwareId(std::string _hId) {
     this.hardware_id = _hId;
 }

 std::string Tracking::getHardwareId() {
     return hardware_id;
 }
