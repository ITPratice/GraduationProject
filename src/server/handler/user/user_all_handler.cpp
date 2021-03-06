#include "user_all_handler.h"

get_all_handler::get_all_handler() {
    data = new DataManager("tracker.db");
}

void get_all_handler::listener(http_request request) {
    if (data->connectDb() != DATA_SUCCESS)
        return;
    if (request.method() == methods::GET) {
        handle_get(request);
    } else if (request.method() == methods::PUT) {
        handle_put(request);
    } else if request.method() == methods::POST) {
        handle_post(request);
    } else if (request.method() == methods::DEL) {
        handle_delete(request);
    }
}

// GET /api/user/all
void get_all_handler::handle_get(http_request request) {
    std::cout << "GET /api/user/all\n";

    std::vector<User> lstUser;
    std::map<std::string, std::string> dictionary;
    std::vector<json::value> vUser;

    if (data->GetAllUser(lstUser) != DATA_SUCCESS) {
        request.reply(status_codes::BadRequest, ResultCode::ERROR);
        return;
    }

    for(int i = 0; i < lstUser.size(); i++) {
        dictionary = user_to_map(lstUser[i]);
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

void get_all_handler::handle_put(http_request request) {
    request.reply(status_codes::BadRequest, ResultCode::NOT_SUPPORT);
}

void get_all_handler::handle_post(http_request request) {
    request.reply(status_codes::BadRequest, ResultCode::NOT_SUPPORT);
}

void get_all_handler::handle_delete(http_request request) {
    request.reply(status_codes::BadRequest, ResultCode::NOT_SUPPORT);
}

std::map<utility::string_t,utility::string_t> get_all_handler::user_to_map(User &user) {
    std::map<utility::string_t, utility::string_t> dictionary;
    dictionary["Email"] = user.getEmail();
    dictionary["Username"] = user.getUsername();
    dictionary["Address"] = user.getAddress();
    dictionary["PhoneNumber"] = user.getPhoneNumber();
    dictionary["Password"] = user.getPassword();
    dictionary["Fullname"] = user.getFullname();
    dictionary["Role"] = stoi(user.getRole());
    dictionary["First"] = stoi(user.getFirst());
    return dictionary;
}