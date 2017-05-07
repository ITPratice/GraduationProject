#include "write_history_handler.h"

WriteHistoryHandler::WriteHistoryHandler() {
    data = new DataManager("tracker.db");
}

void WriteHistoryHandler::listener(http_request request) {
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

void WriteHistoryHandler::handle_get(http_request request) {
    std::cout << "GET /api/vehicle/write\n";
    auto get_vars = uri::split_query(request.request_uri().query());
    if (get_vars.size() != 1) {
        request.reply(status_codes::BadRequest, ResultCode::URL_INVALID);
        return;
    }

    auto _nPlate = uri::decode(get_vars.find("plate")->second);
    if(data->UpdateWriteHistory(_nPlate) != DATA_SUCCESS) {
        request.reply(status_codes::BadRequest, ResultCode::ERROR);
    } else {
        request.reply(status_codes::OK, ResultCode::DONE);
    }
}

void WriteHistoryHandler::handle_put(http_request request) {
    request.reply(status_codes::BadRequest, ResultCode::NOT_SUPPORT);
}

void WriteHistoryHandler::handle_post(http_request request) {
    request.reply(status_codes::BadRequest, ResultCode::NOT_SUPPORT);
}

void WriteHistoryHandler::handle_delete(http_request request) {
    request.reply(status_codes::BadRequest, ResultCode::NOT_SUPPORT);
}