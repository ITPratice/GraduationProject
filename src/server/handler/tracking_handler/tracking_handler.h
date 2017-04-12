#include <iostream>
#include <map>
#include <sstream>
#include <ctime>
#include <iomanip>

#include "../stdafx.h"
#include "../../datalayer/tracking.h"
#include "../../datalayer/data_manager.h"
#include "../../ResponseInterface.h"

#ifndef TRACKING_HANDLER_H
#define TRACKING_HANDLER_H

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

class tracking_handler {
public:
    tracking_handler();
    void listener(http_request request);
private:
    void handle_get(http_request request);
    void handle_put(http_request request);
    void handle_post(http_request request);
    void handle_delete(http_request request);
private:
    DataManager *data;
};

#endif  // TRACKING_HANDLER_H
