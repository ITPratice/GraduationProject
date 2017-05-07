#include "current_time_handler.h"

CurrentTimeHandler::CurrentTimeHandler() {
    data = new DataManager("tracker.db");
}

void CurrentTimeHandler::listener(http_request request) {
    if (data->connectDb() != DATA_SUCCESS)
        return;
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

void CurrentTimeHandler::handle_get(http_request request) {
    std::cout << "CURRENT_TIME_HANDLER - PUT /api/time\n";
    auto get_vars = uri::split_query(request.request_uri().query());
    if (get_vars.size() != 1) {
        request.reply(status_codes::BadRequest, ResultCode::URL_INVALID);
        return;
    }
    auto _plate = uri::decode(get_vars.find("plate")->second);
    int _write;
    if(data->GetWriteHistory(_plate, _write) != DATA_SUCCESS) {
        request.reply(status_codes::BadRequest, ResultCode::ERROR);
        return;
    }

    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H:%M:%S") << " " << _write;
    auto c_time = oss.str();
    request.reply(status_codes::OK, c_time);
}

void CurrentTimeHandler::handle_put(http_request request) {
    std::cout << "CURRENT_TIME_HANDLER - PUT /api/time\n";

    request.reply(status_codes::BadRequest, "Not Support"); 
}

void CurrentTimeHandler::handle_post(http_request request) {
    std::cout << "CURRENT_TIME_HANDLER - PUT /api/time\n";

    request.reply(status_codes::BadRequest, "Not Support"); 
}

void CurrentTimeHandler::handle_delete(http_request request) {
    std::cout << "CURRENT_TIME_HANDLER - PUT /api/time\n";

    request.reply(status_codes::BadRequest, "Not Support"); 
}