#include <iostream>
#include <map>

#include "../stdafx.h"
#include "../../datalayer/vehicle.h"
#include "../../datalayer/data_manager.h"
#include "../../ResponseInterface.h"

#ifndef ALL_VEHICLE_TYPE_HANDLER_H
#define ALL_VEHICLE_TYPE_HANDLER_H

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

class GetAllVehicleTypeHandler {
public:
    GetAllVehicleTypeHandler();
    void listener(http_request request);
private:
    void handle_get(http_request request);
    void handle_put(http_request request);
    void handle_post(http_request request);
    void handle_delete(http_request request);
private:
    std::map<utility::string_t,utility::string_t> vehicleType_to_map(VehicleType &vehicleType);
    DataManager *data;
};

#endif  // ALL_VEHICLE_TYPE_HANDLER_H
