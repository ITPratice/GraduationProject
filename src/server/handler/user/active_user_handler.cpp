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

    std::vector<User> lstUser;
    std::map<std::string, std::string> dictionary;
    std::vector<json::value> vUser;

    if (data->GetAllUserWaiting(lstUser) != DATA_SUCCESS) {
        request.reply(status_codes::BadRequest, ERROR);
        return;
    }

    for(auto _user : lstUser) {
        dictionary = UserToMap(_user);
        json::value json;
        for(auto const& p : dictionary) {
            json[p.first] = json::value::string(p.second);
        }
        vUser.push_back(json);
        dictionary.clear();
    }

    json::value answer;
    answer["data"] = json::value::array(vUser);

    request.reply(status_codes::OK, answer);
}

// PUT /api/user/active?email={email}
void ActiveUserHandler::handle_put(http_request request) {
    std::cout << "PUT /api/user/active?email={email}" << std::endl;
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

void ActiveUserHandler::handle_post(http_request request) {
    std::cout << "POST /api/user/active?email={email}" << std::endl;
    request.reply(status_codes::BadRequest, NOT_SUPPORT);
}

void ActiveUserHandler::handle_delete(http_request request) {
    std::cout << "DELETE /api/user/active?email={email}" << std::endl;
    request.reply(status_codes::BadRequest, NOT_SUPPORT);
}

std::map<utility::string_t, utility::string_t> ActiveUserHandler::UserToMap(User &user) {
    std::map<utility::string_t, utility::string_t> dictionary;
    dictionary["Email"] = user.getEmail();
    dictionary["Username"] = user.getUsername();
    dictionary["Address"] = user.getAddress();
    dictionary["PhoneNumber"] = user.getPhoneNumber();
    dictionary["Password"] = user.getPassword();
    dictionary["Fullname"] = user.getFullname();
    dictionary["Role"] = std::to_string(user.getRole());
    dictionary["First"] = std::to_string(user.getFirst());
    return dictionary;
}