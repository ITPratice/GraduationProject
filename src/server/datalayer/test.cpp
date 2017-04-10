#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

#include "../libs/rest/include/cpprest/http_listener.h"
#include "../libs/rest/include/cpprest/json.h"

#include "../ResponseInterface.h"

#include "data_manager.h"
#include "user_location.h"
#include "user.h"
#include "location.h"

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

DataManager data("test.db");
std::map<std::string, std::string> dictionary;

void handle_get(http_request request);
std::map<std::string, std::string> user_to_map(User &user);

int main()
{
    if (data.connectDb() != DATA_SUCCESS)
    {
        std::cout << "ERROR" << std::endl;
        return 1;
    }
    User user("1", "duvuthacu261@gmail.com", "Hanoi", "01684778056", "29V5-4628", "123456", ADMIN_GROUP);
    User _user1("2", "cuongdvt261@gmail.com", "Hanoi", "0123456789", "29V5-4628", "654178", USER_GROUP);
    User _user2("3", "thaicuong@gmail.com", "Hanoi", "987654321", "29V5-4628", "879563", USER_GROUP);

    if (data.InsertUser(user) != DATA_SUCCESS)
    {
        std::cout << "EROR" << std::endl;
        return 1;
    }
    else
    {
        std::cout << "INSERT SUCCESS" << std::endl;
    }

    if (data.InsertUser(_user1) != DATA_SUCCESS) {
        std::cout << "EROR" << std::endl;
        return 1;
    }
    else {
        std::cout << "INSERT SUCCESS" << std::endl;
    }

    if (data.InsertUser(_user2) != DATA_SUCCESS) {
        std::cout << "EROR" << std::endl;
        return 1;
    }
    else {
        std::cout << "INSERT SUCCESS" << std::endl;
    }

    http_listener listener("http://localhost:3000/user/all");
    listener.support(methods::GET, handle_get);

        listener.open().wait();
        while(true);

    return 0;
}

void handle_get(http_request request) {
    std::cout << "Handle GET\n";
    std::vector<User> lstUser;
    if (data.GetAllUser(lstUser) != DATA_SUCCESS) {
        std::cout << "ERROR" << std::endl;
        return;
    }

    std::vector<json::value> vUser;

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
    answer["allUser"] = json::value::array(vUser);

    request.reply(status_codes::OK, answer);
}

std::map<std::string, std::string> user_to_map(User &user) {
    std::map<std::string, std::string> dictionary;
    dictionary["Id"] = user.getId();
    dictionary["Email"] = user.getEmail();
    dictionary["Address"] = user.getAddress();
    dictionary["PhoneNumber"] = user.getPhoneNumber();
    dictionary["Password"] = user.getPassword();
    dictionary["NumberPlate"] = user.getNumberPlate();
    return dictionary;
}