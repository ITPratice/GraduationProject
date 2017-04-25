#include <iostream>
#include <map>

#include "../stdafx.h"

#ifndef VEHICLE_TYPE_HANDLER_H
#define VEHICLE_TYPE_HANDLER_H

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

class VehicleTypeHandler {
public:
    VehicleTypeHandler();
    void listener(http_request request);
private:
    void handle_get(http_request request);
    void handle_put(http_request request);
    void handle_post(http_request request);
    void handle_delete(http_request request);
private:
    DataManager *data;
};

#endif  // USER_HANDLER_H