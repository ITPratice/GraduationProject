#include <iostream>
#include <map>

#include "../stdafx.h"
#include "../../datalayer/user.h"
#include "../../datalayer/data_manager.h"
#include "../../ResponseInterface.h"

#ifndef GET_ALL_HANDLER_H
#define GET_ALL_HANDLER_H

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

class get_all_handler {
public:
    get_all_handler();
    void listener(http_request request);
private:
    void handle_get(http_request request);
    void handle_put(http_request request);
    void handle_post(http_request request);
    void handle_delete(http_request request);
private:
    std::map<utility::string_t,utility::string_t> user_to_map(User &user);
    DataManager *data;
};

#endif
