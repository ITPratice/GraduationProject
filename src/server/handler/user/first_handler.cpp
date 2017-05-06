#include "first_handler.h"

FirstHandler::FirstHandler() {
    data = new DataManager("tracker.db");
}

void FirstHandler::listener(http_request request) {
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

// GET /api/user/first?email={email}&pass={pass}
void FirstHandler::handle_get(http_request request) {
    std::cout << "GET /api/user/first?email={email}&pass={pass}\n";
    auto get_vars = uri::split_query(request.request_uri().query());
    if (get_vars.size() != 2) {
        request.reply(status_codes::BadRequest, URL_INVALID);
        return;
    }

    auto _email = uri::decode(get_vars.find("email")->second);
    auto _newPass = uri::decode(get_vars.find("pass")->second);
    if(data->ChangePassIfFirst(_newPass, _email) == DATA_SUCCESS) {
        request.reply(status_codes::OK, DONE);
    } else {
        request.reply(status_codes::BadRequest, ERROR);
    }
}

// PUT /api/user/first?email={email}&pass={pass}
void FirstHandler::handle_put(http_request request) {
    std::cout << "PUT /api/user/first?email={email}&pass={pass}\n";
    request.reply(status_codes::BadRequest, NOT_SUPPORT);
}

void FirstHandler::handle_post(http_request request) {
    std::cout << "POST /api/user/first?email={email}&pass={pass}\n";
    request.reply(status_codes::BadRequest, NOT_SUPPORT);
}

void FirstHandler::handle_delete(http_request request) {
    std::cout << "DELETE /api/user/first?email={email}&pass={pass}\n";
    request.reply(status_codes::BadRequest, NOT_SUPPORT);
}