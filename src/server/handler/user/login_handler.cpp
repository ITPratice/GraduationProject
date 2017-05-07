#include "login_handler.h"
#include <iostream>

LoginHandler::LoginHandler() {
    data = new DataManager("tracker.db");
}

void LoginHandler::listener(http_request request) {
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

// GET /api/user/login
void LoginHandler::handle_get(http_request request) {
    std::cout << "GET /api/user/login\n";
    User _outUser;
    auto get_vars = uri::split_query(request.request_uri().query());
    if (get_vars.size() != 2) {
        request.reply(status_codes::BadRequest, ResultCode::URL_INVALID);
        return;
    }
    auto _email = uri::decode(get_vars.find("email")->second);
    auto _pass = uri::decode(get_vars.find("pass")->second);
    if(data->Login(_email, _pass) != DATA_SUCCESS) {
        request.reply(status_codes::BadRequest, ResultCode::ERROR);
        return;
    }

    if(data->GetUserByEmail(_email, _outUser) == DATA_SUCCESS) {
        if(_outUser.getFirst() == 1) {
            request.reply(status_codes::OK, ResultCode::FIRST_LOGIN);
        } else {
            request.reply(status_codes::OK, ResultCode::NOT_FIRST_LOGIN);
        }
    } else {
        request.reply(status_codes::BadRequest, ResultCode::ERROR);
    }
}

// PUT /api/user/login
void LoginHandler::handle_put(http_request request) {
    std::cout << "PUT /api/user/login\n";
    request.reply(status_codes::BadRequest, ResultCode::NOT_SUPPORT);
}

// POST /api/user/login
void LoginHandler::handle_post(http_request request) {
    std::cout << "POST /api/user/login\n";
    request.reply(status_codes::BadRequest, ResultCode::NOT_SUPPORT);
}

// DELETE /api/user/login
void LoginHandler::handle_delete(http_request request) {
    std::cout << "DELETE /api/user/login\n";
    request.reply(status_codes::BadRequest, ResultCode::NOT_SUPPORT);
}