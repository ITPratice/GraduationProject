#include "../stdafx.h"
#include "../../datalayer/data_manager.h"
#include "../../datalayer/user.h"
#include "../../ResponseInterface.h"

#ifndef LOGIN_HANDLER_H
#define LOGIN_HANDLER_H

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

class LoginHandler {
public:
    LoginHandler();
    void listener(http_request request);
private:
    void handle_get(http_request request);
    void handle_put(http_request request);
    void handle_post(http_request request);
    void handle_delete(http_request request);
private:
    DataManager *data;
};

#endif  // LOGIN_HANDLER_H