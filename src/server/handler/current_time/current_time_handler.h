#include "../stdafx.h"

#ifndef CURRENT_TIME_HANDLER_H
#define CURRENT_TIME_HANDLER_H

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

class CurrentTimeHandler {
public:
    CurrentTimeHandler();
    void listener(http_request request);
private:
    void handle_get(http_request request);
    void handle_put(http_request request);
    void handle_post(http_request request);
    void handle_delete(http_request request);
};

#endif  // CURRENT_TIME_HANDLER_H