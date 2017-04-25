#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

#include "stdafx.h"

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

void routingHandler(http_request request);

std::unique_ptr<UserHandler> userHandler;
std::unique_ptr<LocationHandler> locationHandler;

int main()
{
    http_listener listener("http://0.0.0.0:3000/");
    listener.support(routingHandler);
    listener.open().wait();
    while(true);
    return 0;
}

void routingHandler(http_request request) {
    utility::string_t routePath = request.relative_uri().path();
    switch(string_helper::hash_str(routePath)) {
        case ROUTE_USER:
            userHandler = std::unique_ptr<UserHandler>(new UserHandler());
            userHandler->listener(request);
            break;
        case ROUTE_LOCATION:
            locationHandler = std::unique_ptr<LocationHandler>(new LocationHandler());
            locationHandler->listener();
            break;
        default:
            break;
    }
}

