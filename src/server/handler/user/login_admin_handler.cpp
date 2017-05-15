#include "login_admin_handler.h"

LoginAdminHandler::LoginAdminHandler() {
    data = new DataManager("tracker.db");
}

void LoginAdminHandler::listener(http_request request) {
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

// GET /api/admin/login
void LoginAdminHandler::handle_get(http_request request) {
    std::cout << "GET /api/admin/login\n";
    auto get_vars = uri::split_query(request.request_uri().query());
    if (get_vars.size() != 2) {
        request.reply(status_codes::BadRequest, ResultCode::URL_INVALID);
        return;
    }
    auto _email = uri::decode(get_vars.find("email")->second);
    auto _pass = uri::decode(get_vars.find("pass")->second);
    if(data->LoginAdmin(_email, _pass) == DATA_SUCCESS) {
        request.reply(status_codes::BadRequest, ResultCode::DONE);
    } else {
        request.reply(status_codes::BadRequest, ResultCode::ERROR);
    }

}

// PUT /api/admin/login
void LoginAdminHandler::handle_put(http_request request) {
    std::cout << "PUT /api/admin/login\n";
    request.reply(status_codes::BadRequest, ResultCode::NOT_SUPPORT);
}

// POST /api/admin/login
void LoginAdminHandler::handle_post(http_request request) {
    std::cout << "POST /api/admin/login\n";
    request.reply(status_codes::BadRequest, ResultCode::NOT_SUPPORT);
}

// DELETE /api/admin/login
void LoginAdminHandler::handle_delete(http_request request) {
    std::cout << "DELETE /api/user/login\n";
    request.reply(status_codes::BadRequest, ResultCode::NOT_SUPPORT);
}