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
std::unique_ptr<CurrentTimeHandler> currentTime;
std::unique_ptr<AllUserHandler> allUserHandler;
std::unique_ptr<CurrentLocationHandler> curLocationHandler;
std::unique_ptr<ArduinoLocation> arLocationHandler;
std::unique_ptr<LoginAdminHandler> aLoginHandler;
std::unique_ptr<LoginHandler> uLoginHandler;
std::unique_ptr<VehiclePlateByUserHandler> plateByUserHandler;
std::unique_ptr<ActiveUserHandler> activeUserHandler;
std::unique_ptr<FirstHandler> firstHandler;
std::unique_ptr<GetAllBranchHandler> allBranchHandler;
std::unique_ptr<GetAllVehicleHandler> allVehiclehandler;
std::unique_ptr<GetAllVehicleTypeHandler> allVehicleTypeHandler;

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
        case ROUTE_CURRENT_TIME:
            currentTime = std::unique_ptr<CurrentTimeHandler>(new CurrentTimeHandler());
            currentTime->listener(request);
            break;
        case ROUTE_USER_ALL:
            allUserHandler = std::unique_ptr<AllUserHandler>(new AllUserHandler());
            allUserHandler->listener(request);
            break;
        case ROUTE_LOCATION_CURRENT:
            curLocationHandler = std::unique_ptr<CurrentLocationHandler>(new CurrentLocationHandler());
            curLocationHandler->listener(request);
            break;
        case ROUTE_ARDUINO_LOCATION:
            arLocationHandler = std::unique_ptr<ArduinoLocation>(new ArduinoLocation());
            arLocationHandler->listener(request);
            break;
        case ROUTE_ADMIN_LOGIN:
            aLoginHandler = std::unique_ptr<LoginAdminHandler>(new LoginAdminHandler());
            aLoginHandler->listener(request);
            break;
        case ROUTE_USER_LOGIN:
            uLoginHandler = std::unique_ptr<LoginHandler>(new LoginHandler());
            uLoginHandler->listener(request);
            break;
        case ROUTE_VEHICLEPLATE_BYUSER:
            plateByUserHandler = std::unique_ptr<VehiclePlateByUserHandler>(new VehiclePlateByUserHandler());
            plateByUserHandler->listener(request);
            break;
        case ROUTE_ACTIVE_USER:
            activeUserHandler = std::unique_ptr<ActiveUserHandler>(new ActiveUserHandler());
            activeUserHandler->listener(request);
            break;
        case ROUTE_CHANGE_PASS_IF_FIRST:
            firstHandler = std::unique_ptr<FirstHandler>(new FirstHandler());
            firstHandler->listener(request);
            break;
        case ROUTE_VEHICLE_ALL:
            allVehiclehandler = std::unique_ptr<GetAllVehicleHandler>(new GetAllVehicleHandler());
            allVehiclehandler->listener(request);
            break;
        case ROUTE_VEHICLE_TYPE_ALL:
            allVehicleTypeHandler = std::unique_ptr<GetAllVehicleTypeHandler>(new GetAllVehicleTypeHandler());
            allVehicleTypeHandler->listener(request);
            break;
        case ROUTE_BRANCH_ALL:
            allBranchHandler = std::unique_ptr<GetAllBranchHandler>(new GetAllBranchHandler());
            allBranchHandler->listener(request);
            break;
        default:
            break;
    }
}

