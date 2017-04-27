#include "current_time_handler.h"

CurrentTimeHandler::CurrentTimeHandler() {

}

void CurrentTimeHandler::listener(http_request request) {
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
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H:%M:%S");
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