#include "login_handler.h"

login_handler::login_handler() {
    data = new DataManager("test.db");
}

void login_handler::listener(http_request request) {
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

// GET /api/user/all
void login_handler::handle_get(http_request request) {
    std::cout << "GET /api/login/user\n";

    auto get_vars = uri::split_query(request.request_uri().query());
    if(get_vars.empty()) {
        request.reply(status_codes::BadRequest, "Query null");
        return;
    }
    auto found_email = get_vars.find("email");
    auto found_pass = get_vars.find("pass");
    if(found_email == get_vars.end() || found_pass == get_vars.end()) {
        request.reply(status_codes::BadRequest, "Value null");
        return;
    }

    auto email = found_email->second;
    auto pass = found_pass->second;

    if(data->Login(email, pass) == DATA_SUCCESS) {
        request.reply(status_codes::OK, json::value::string("OK"));
    } else {
        request.reply(status_codes::OK, json::value::string("ERROR"));
    }
}

void login_handler::handle_put(http_request request) {
    request.reply(status_codes::OK, "Not support");
}

void login_handler::handle_post(http_request request) {
    request.reply(status_codes::OK, "Not support");
}

void login_handler::handle_delete(http_request request) {
    request.reply(status_codes::OK, "Not support");
}