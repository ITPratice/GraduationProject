#include "../stdafx.h"
#include "../../datalayer/data_manager.h"
#include "../../datalayer/location.h"
#include "../../ResponseInterface.h"

#ifndef LOCATION_HANDLER_H
#define LOCATION_HANDLER_H

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

class LocationHandler {
public:
    LocationHandler();
    void listener(http_request request);
private:
    void handle_get(http_request request);
    void handle_put(http_request request);
    void handle_post(http_request request);
    void handle_delete(http_request request);
private:
    std::map<utility::string_t, utility::string_t> LocationToMap(Location &location);
    DataManager *data;
};

#endif  // LOCATION_HANDLER_H