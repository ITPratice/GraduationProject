#include "user_handler.h"

user_handler::user_handler() {
    data = new DataManager("test.db");
}

void user_handler::listener () {
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

void user_handler::handle_get(http_request request) {
    std::cout << "GET /api/user\n";
}

void user_handler::handle_put(http_request request) {

}

void user_handler::handle_post(http_request request) {
    std::cout << "POST /api/user\n";

    auto get_vars = uri::split_query(request.request_uri().query());
    if(get_vars.empty()) {
        request.reply(status_codes::BadRequest, "Query is null");
        return;
    }
    auto found_email = get_vars.find("email");
    auto found_uname = get_vars.find("username");
    auto found_addr = get_vars.find("address");
    auto found_phone = get_vars.find("phone");
    auto found_pass = get_vars.find("pass");
    if(found_email == get_vars.end() || found_uname == get_vars.end()  || found_addr == get_vars.end()  ||found_phone == get_vars.end()||found_pass == get_vars.end()) {
        request.reply(status_codes::BadRequest, "Value is null");
        return;
    }

    auto email = found_email->second;
    auto uname = found_uname->second;
    auto addr = found_addr->second;
    auto phone = found_phone->second;
    auto pass = found_pass->second;
    User _user User(email, uname, addr, phone, pass, 0, 0);

    if(data->InsertUser(email, pass) == DATA_SUCCESS) {
        request.reply(status_codes::OK, json::value::string("OK"));
    } else {
        request.reply(status_codes::OK, json::value::string("ERROR"));
    }
}

void user_handler::handle_delete(http_request request) {

}