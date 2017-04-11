#include <iostream>
#include <map>

#include "../stdafx.h"
#include "../../datalayer/location.h"
#include "../../datalayer/data_manager.h"
#include "../../ResponseInterface.h"

#ifndef LOCATION_TIME_H
#define LOCATION_TIME_H

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

class location_time {
public:
    location_time();
    void ltListener(http_request request);
private:
    void ltHandle_get(http_request request);
    void ltHandle_put(http_request request);
    void ltHandle_post(http_request request);
    void ltHandle_delete(http_request request);
private:
    DataManager *data;
};

#endif