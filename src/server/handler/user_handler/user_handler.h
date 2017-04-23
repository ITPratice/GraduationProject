#include <iostream>
#include <map>

#include "../stdafx.h"
#include "../../datalayer/user.h"
#include "../../datalayer/data_manager.h"
#include "../../ResponseInterface.h"

#ifndef USER_HANDLER
#define USER_HANDLER

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

class user_handler {
public:
    user_handler();
    void listener(http_request request);
private:
    void handle_get(http_request request);
    void handle_put(http_request request);
    void handle_post(http_request request);
    void handle_delete(http_request request);
private:
    DataManager *data;
}

#endif