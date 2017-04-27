#include "current_location_handler.h"

CurrentLocationHandler::CurrentLocationHandler() {
    data = new DataManager("tracker.db");
}

void CurrentLocationHandler::listener(http_request request) {
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

void CurrentLocationHandler::handle_get(http_request request) {
    std::cout << "LOCATION_HANDLER - GET /api/location\n";
    auto get_vars = uri::split_query(request.request_uri().query());
    if (get_vars.empty()) {
        request.reply(status_codes::BadRequest, "Query null");
        return;
    }

    Location _location;
    auto _nPlate = string_helper::replace_space(get_vars.find("plate")->second);
    if (data->GetCurrentLocation(_nPlate, _location) != DATA_SUCCESS) {
        request.reply(status_codes::BadRequest, "ERROR");
        return;
    }

    json::value _jValue;
    _jValue["Latitude"] = json::value::string(_location.getLatitude());
    _jValue["Longitude"] = json::value::string(_location.getLongititu());
    _jValue["NumberPlate"] = json::value::string(_location.getNumberPlate());
    _jValue["Date"] = json::value::string(_location.getDate());
    _jValue["StartTime"] = json::value::string(_location.getStartTime());
    _jValue["EndTime"] = json::value::string(_location.getEndTime());

    request.reply(status_codes::OK, _jValue); 
}

// GET /api/location/current
void CurrentLocationHandler::handle_put(http_request request) {
    std::cout << "LOCATION_HANDLER - PUT /api/location/current\n";

    request.reply(status_codes::BadRequest, "Not Support"); 
}

void CurrentLocationHandler::handle_post(http_request request) {
    std::cout << "LOCATION_HANDLER - POST /api/location/current\n";

    request.reply(status_codes::BadRequest, "Not Support"); 
}

// DELETE /api/location/current
void CurrentLocationHandler::handle_delete(http_request request) {
    std::cout << "LOCATION_HANDLER - DELETE /api/location/current\n";

    request.reply(status_codes::BadRequest, "Not Support"); 
}