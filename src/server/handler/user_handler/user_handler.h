#include <iostream>
#include "../stdafx.h"
#include "../../datalayer/data_manager.h"
#include "../../datalayer/user.h"
#include "../../ResponseInterface.h"

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

class user_handler {
public:
    user_handler();
    user_handler(utility::string_t url);
    virtual ~user_handler();
public:
    pplx::task<void>open() { return m_listener.open(); }
    pplx::task<void>close() { return m_listener.close(); }
private:
    void handle_get(http_request request);
    void handle_put(http_request request);
    void handle_post(http_request request);
    void handle_delete(http_request request);

    void handle_login(http_request request);
private:
    http_listener m_listener;
};
