#include "active_user_handler.h"

ActiveUserHandler::ActiveUserHandler() {
    data = new DataManager("tracker.db");
}

void ActiveUserHandler::listener(http_request request) {
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

// GET /api/user/active?email={email}
void ActiveUserHandler::handle_get(http_request request) {
    std::cout << "GET /api/user/active?email={email}" << std::endl;

    auto get_vars = uri::split_query(request.request_uri().query());
    if (get_vars.size() != 1) {
        request.reply(status_codes::BadRequest, URL_INVALID);
        return;
    }

    auto _email = uri::decode(get_vars.find("email")->second);
    if(data->ActiveUser(_email) == DATA_SUCCESS) {
        request.reply(status_codes::OK, DONE);
    } else {
        request.reply(status_codes::BadRequest, ERROR);
    }
}


void ActiveUserHandler::handle_put(http_request request) {
    std::cout << "PUT /api/user/active?email={email}" << std::endl;
    request.reply(status_codes::BadRequest, NOT_SUPPORT);
}

void ActiveUserHandler::handle_post(http_request request) {
    std::cout << "POST /api/user/active?email={email}" << std::endl;
    request.reply(status_codes::BadRequest, NOT_SUPPORT);
}

void ActiveUserHandler::handle_delete(http_request request) {
    std::cout << "DELETE /api/user/active?email={email}" << std::endl;
    request.reply(status_codes::BadRequest, NOT_SUPPORT);
}