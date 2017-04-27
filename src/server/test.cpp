#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

#include "stdafx.h"
#include "helper/string_helper.h"

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

void RoutingHandler(http_request request);

std::unique_ptr<UserHandler> userHandler;
std::unique_ptr<LocationHandler> locationHandler;
std::unique_ptr<BranchHandler> branchHandler;
std::unique_ptr<VehicleHandler> vehicleHandler;
std::unique_ptr<VehicleTypeHandler> t_vehicleHandler;

int main()
{
    http_listener listener("http://0.0.0.0:3000");
    listener.support(RoutingHandler);
    listener.open().wait();
    while(true);
    return 0;
}

void RoutingHandler(http_request request) {
    utility::string_t routePath = request.relative_uri().path();
    switch(string_helper::hash_str(routePath)) {
        case ROUTE_USER:
            userHandler = std::unique_ptr<UserHandler>(new UserHandler());
            userHandler->listener(request);
            break;
        case ROUTE_LOCATION:
            locationHandler = std::unique_ptr<LocationHandler>(new LocationHandler());
            locationHandler->listener(request);
            break;
        case ROUTE_BRANCH:
            branchHandler = std::unique_ptr<BranchHandler>(new BranchHandler());
            branchHandler->listener(request);
            break;
        case ROUTE_VEHICLE:
            vehicleHandler = std::unique_ptr<VehicleHandler>(new VehicleHandler());
            vehicleHandler->listener(request);
            break;
        case ROUTE_VEHICLE_TYPE:
            t_vehicleHandler = std::unique_ptr<VehicleTypeHandler>(new VehicleTypeHandler());
            t_vehicleHandler->listener(request);
            break;
        default:
            break;
    }
}

