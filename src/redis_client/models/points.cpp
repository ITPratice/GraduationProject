#include "points.hpp"

~Points::Points() {

}

Points::Points(std::string latPoint, std::string lonPoint) {
    lat_point = latPoint;
    lon_point = lonPoint;
}

std::string Points::get_lat_point() {
    return lat_point;
}

void Points::set_lat_point(std::string latPoint) {
    lat_point = latPoint;
}

std::string Points::get_lon_point() {
    return lon_point;
}

void Points::get_lon_point(std::string lonPoint) {
    lon_point = lonPoint;
}