#include "../stdafx.h"
#include "../../datalayer/data_manager.h"
#include "../../datalayer/location.h"
#include "../../ResponseInterface.h"

#ifndef LOCATION__H
#define LOCATION__H

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

class ArduinoLocation {
public:
    ArduinoLocation();
    void listener(http_request request);
private:
    void handle_get(http_request request);
    void handle_put(http_request request);
    void handle_post(http_request request);
    void handle_delete(http_request request);
private:
    DataManager *data;
};

#endif  // LOCATION__H