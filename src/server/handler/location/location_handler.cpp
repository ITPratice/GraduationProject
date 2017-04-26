#include "location_handler.h"

LocationHandler::LocationHandler() { 
    data = new DataManager("tracker.db");
}

void LocationHandler::listener(http_request request) {
    if (data->connectDb() != DATA_SUCCESS) {
        return;
    }
    if (request.method() == methods::GET) {
        handle_get(request);
    } else if (request.method() == methods::PUT) {
        handle_put(request);
    } else if (request.method() == methods::POST) {
        handle_post(request);
    } else if (request.method() == methods::DEL) {
        handle_delete(request);
    }
}

// GET api/location
void LocationHandler::handle_get(http_request request) {
    std::cout << "LOCATION_HANDLER - GET /api/location\n";

    request.reply(status_codes::BadRequest, "Not Support"); 
}

// POST /api/location
void LocationHandler::handle_post(http_request request) {
    std::cout << "LOCATION_HANDLER - POST /api/location\n";

    auto get_vars = uri::split_query(request.request_uri().query());
    if (get_vars.empty()) {
        request.reply(status_codes::BadRequest, "Query null");
        return;
    }

    // Get value from api query
    auto _lat = string_helper::replace_space(get_vars.find("lat")->second);
    auto _lon = string_helper::replace_space(get_vars.find("lon")->second);
    auto _nPlate = string_helper::replace_space(get_vars.find("plate")->second);
    auto _date = string_helper::replace_space(get_vars.find("date")->second);
    auto _start = string_helper::replace_space(get_vars.find("start")->second);

    // Get DateTime.Now
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream osDate, osTime;
    osTime << std::put_time(&tm, "%H:%M:%S"); 
    auto c_time = osTime.str();

    // Init new Location
    Location _location;
    _location.setLatitude(_lat);
    _location.setLongititu(_lon);
    _location.setNumberPlate(_nPlate);
    _location.setDate(_date);
    _location.setStartTime(_start);
    _location.setEndTime(c_time);

    if (data->InsertLocation(_location) == DATA_SUCCESS) {
        request.reply(status_codes::OK, json::value::string("SUCCESS"));
    } else {
        request.reply(status_codes::BadRequest, json::value::string("ERROR"));
    }
}

// PUT api/location
void LocationHandler::handle_put(http_request request) {
    std::cout << "LOCATION_HANDLER - PUT /api/location\n";

    request.reply(status_codes::BadRequest, "Not Support"); 
}

// DELETE api/location
void LocationHandler::handle_delete(http_request request) {
    std::cout << "LOCATION_HANDLER - DELETE /api/location\n";

    request.reply(status_codes::BadRequest, "Not Support"); 
}