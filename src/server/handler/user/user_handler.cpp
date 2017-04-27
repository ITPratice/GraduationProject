#include "user_handler.h"

UserHandler::UserHandler() {
    data = new DataManager("tracker.db");
}

void UserHandler::listener(http_request request) {
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

// GET /api/user?email={}
void UserHandler::handle_get(http_request request) {
    std::cout << "GET /api/user?email\n";
    User outUser;
    auto get_vars = uri::split_query(request.request_uri().query());
    if (get_vars.empty()) {
        request.reply(status_codes::BadRequest, "Query is null");
        return;
    }

    // Get user by email
    auto _email = get_vars.find("email")->second;
    if (data->GetUserByEmail(_email, outUser) != DATA_SUCCESS) {
        request.reply(status_codes::BadRequest, json::value::string("Query Error"));
        return;
    }

    // Set User json
    json::value _jValue;
    _jValue["Email"] = json::value::string(outUser.getEmail());
    _jValue["Username"] = json::value::string(outUser.getUsername());
    _jValue["Address"] = json::value::string(outUser.getAddress());
    _jValue["PhoneNumber"] = json::value::string(outUser.getPhoneNumber());
    _jValue["Password"] = json::value::string(outUser.getPassword());
    _jValue["Fullname"] = json::value::string(outUser.getFullname());
    _jValue["Role"] = json::value::number(outUser.getRole());

    request.reply(status_codes::OK, _jValue);
}

// PUT /api/user
void UserHandler::handle_put(http_request request) {
    std::cout << "PUT /api/user\n";

    auto get_vars = uri::split_query(request.request_uri().query());
    if (get_vars.empty()) {
        request.reply(status_codes::BadRequest, "Query is null");
        return;
    }

    // Get user values from query
    auto email = string_helper::replace_space(get_vars.find("email")->second);
    auto uname = string_helper::replace_space(get_vars.find("username")->second);
    auto addr = string_helper::replace_space(get_vars.find("address")->second);
    auto phone = string_helper::replace_space(get_vars.find("phone")->second);
    auto pass = string_helper::replace_space(get_vars.find("pass")->second);
    auto fname =  string_helper::replace_space(get_vars.find("name")->second);
    auto role = string_helper::replace_space(get_vars.find("role")->second);
    User _user(email, uname, addr, phone, fname, pass, stoi(role));

    // Update User
    if (data->UpdateUser(_user) == DATA_SUCCESS) {
        request.reply(status_codes::OK, json::value::string("OK"));
    } else {
        request.reply(status_codes::BadRequest, json::value::string("ERROR"));
    }
}

void UserHandler::handle_post(http_request request) {
    std::cout << "POST /api/user\n";

    auto get_vars = uri::split_query(request.request_uri().query());
    if (get_vars.empty()) {
        request.reply(status_codes::BadRequest, "Query is null");
        return;
    }

    // Get user values from query
    auto email = string_helper::replace_space(get_vars.find("email")->second);
    auto uname = string_helper::replace_space(get_vars.find("username")->second);
    auto addr = string_helper::replace_space(get_vars.find("address")->second);
    auto phone = string_helper::replace_space(get_vars.find("phone")->second);
    auto pass = string_helper::replace_space(get_vars.find("pass")->second);
    auto fname =  string_helper::replace_space(get_vars.find("name")->second);
    auto role = string_helper::replace_space(get_vars.find("role")->second);
    User _user(email, uname, addr, phone, fname, pass, stoi(role));

    if (data->InsertUser(_user) == DATA_SUCCESS) {
        request.reply(status_codes::OK, json::value::string("OK"));
    } else {
        request.reply(status_codes::BadRequest, json::value::string("ERROR"));
    }
}

// DELETE /api/user
void UserHandler::handle_delete(http_request request) {
    std::cout << "DELETE /api/user\n";

    auto get_vars = uri::split_query(request.request_uri().query());
    if(get_vars.empty()) {
        request.reply(status_codes::BadRequest, "Query is null");
        return;
    }

    // Get user values from query
    auto email = string_helper::replace_space(get_vars.find("email")->second);
    auto uname = string_helper::replace_space(get_vars.find("username")->second);
    auto addr = string_helper::replace_space(get_vars.find("address")->second);
    auto phone = string_helper::replace_space(get_vars.find("phone")->second);
    auto pass = string_helper::replace_space(get_vars.find("pass")->second);
    auto fname =  string_helper::replace_space(get_vars.find("name")->second);
    auto role = string_helper::replace_space(get_vars.find("role")->second);
    User _user(email, uname, addr, phone, fname, pass, stoi(role));

    if (data->DeleteUser(_user) == DATA_SUCCESS) {
        request.reply(status_codes::OK, json::value::string("OK"));
    } else {
        request.reply(status_codes::BadRequest, json::value::string("ERROR"));
    }
}