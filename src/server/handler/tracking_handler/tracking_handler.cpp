#include "tracking_handler.h"

tracking_handler::tracking_handler() {
    data = new DataManager("test.db");
}

void tracking_handler::listener(http_request request) {
    if (data->connectDb() != DATA_SUCCESS)
        return;
    if(request.method() == methods::GET) {
        handle_get(request);
    } else if(request.method() == methods::PUT) {
        handle_put(request);
    } else if(request.method() == methods::POST) {
        handle_post(request);
    } else if(request.method() == methods::DEL) {
        handle_delete(request);
    }
}

void tracking_handler::handle_get(http_request request) {
    std::cout << "GET /api/tracking\n";
    Tracking _tracking;
    auto get_vars = uri::split_query(request.request_uri().query());
    if(get_vars.empty()) {
        request.reply(status_codes::BadRequest, "Query null");
        return;
    }
    auto found_lat = get_vars.find("lat");
    auto found_lon = get_vars.find("lon");
    auto found_hId = get_vars.find("hId");
    if(found_lat == get_vars.end() || found_lon == get_vars.end() || found_hId == get_vars.end()) {
        request.reply(status_codes::BadRequest, "Value null");
        return;
    }

    auto lat = found_lat->second;
    auto lon = found_lon->second;
    auto hId = found_hId->second;

    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream osDate, osTime;
    osDate << std::put_time(&tm, "%d-%m-%Y"); auto c_date = osDate.str();
    osTime << std::put_time(&tm, "%H-%M-%S"); auto c_time = osTime.str();

    _tracking.setLatitude(lat);
    _tracking.setLongititu(lon);
    _tracking.setHardwareId(hId);
    _tracking.setDate(c_date);
    _tracking.setTime(c_time);

    if(data->InsertTracking(_tracking) == DATA_SUCCESS) {
        request.reply(status_codes::OK, json::value::string("SUCCESS"));
    } else {
        request.reply(status_codes::OK, json::value::string("ERROR"));
    }
}

void tracking_handler::handle_put(http_request request) {
    std::cout << "PUT /api/tracking\n";
    request.reply(status_codes::OK, "Not support");
}

void tracking_handler::handle_post(http_request request) {
    std::cout << "POST /api/tracking\n";
    request.reply(status_codes::OK, "Not support");
}

void tracking_handler::handle_delete(http_request request) {
    std::cout << "DELETE /api/tracking\n";
    request.reply(status_codes::OK, "Not support");
}