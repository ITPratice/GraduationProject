#include "user_location.h"

UserLocation::UserLocation() {
    user_id = "";
    location_id = "";
    time = "";
}

UserLocation::UserLocation(std::string uId, std::string lId, std::string _time) {
    user_id = uId;
    location_id = lId;
    time = _time;
}

void UserLocation::setUserId(std::string uId) {
    user_id = uId;
}

std::string UserLocation::getUserId() const {
    return user_id;
}

void UserLocation::setLocationId(std::string lId) {
    location_id = lId;
}

std::string UserLocation::getLocationId() const {
    return location_id;
}

void UserLocation::setTime(std::string _time) {
    time = _time;
}

std::string UserLocation::getTime() const {
    return time;
}
