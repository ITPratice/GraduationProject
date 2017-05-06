#include "all_user_handler.h"

AllUserHandler::AllUserHandler() {
    data = new DataManager("tracker.db");
}

void AllUserHandler::listener(http_request request) {
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
void AllUserHandler::handle_get(http_request request) {
    std::cout << "GET /api/user/all\n";

    std::vector<User> lstUser;
    std::map<std::string, std::string> dictionary;
    std::vector<json::value> vUser;

    if (data->GetAllUser(lstUser) != DATA_SUCCESS) {
        request.reply(status_codes::BadRequest, "ERROR");
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

void AllUserHandler::handle_put(http_request request) {
    request.reply(status_codes::BadRequest, "Not support");
}

void AllUserHandler::handle_post(http_request request) {
    request.reply(status_codes::BadRequest, "Not support");
}

void AllUserHandler::handle_delete(http_request request) {
    request.reply(status_codes::BadRequest, "Not support");
}

std::map<utility::string_t, utility::string_t> AllUserHandler::UserToMap(User &user) {
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