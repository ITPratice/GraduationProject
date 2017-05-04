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
    if (get_vars.empty()) {
        request.reply(status_codes::BadRequest, "Query is null");
        return;
    }
    auto _email = uri::decode(get_vars.find("email")->second);
    auto _pass = uri::decode(get_vars.find("pass")->second);
    if(data->Login(_email, _pass) != DATA_SUCCESS) {
        request.reply(status_codes::BadRequest, json::value::string("ERROR 1"));
        return;
    }

    if(data->GetUserByEmail(_email, _outUser) == DATA_SUCCESS) {
        if(_outUser.getFirst() == 1) {
            request.reply(status_codes::OK, json::value::string("FIRST"));
        } else {
            request.reply(status_codes::OK, json::value::string("NOT FIRST"));
        }
    } else {
        request.reply(status_codes::BadRequest, json::value::string("ERROR 2"));
    }
}

// PUT /api/user/login
void LoginHandler::handle_put(http_request request) {
    std::cout << "PUT /api/user/login\n";
    request.reply(status_codes::BadRequest, "Not support");
}

// POST /api/user/login
void LoginHandler::handle_post(http_request request) {
    std::cout << "POST /api/user/login\n";
    request.reply(status_codes::BadRequest, "Not support");
}

// DELETE /api/user/login
void LoginHandler::handle_delete(http_request request) {
    std::cout << "DELETE /api/user/login\n";
    request.reply(status_codes::BadRequest, "Not support");
}