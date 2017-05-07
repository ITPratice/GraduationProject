#include "all_vehicle_type_handler.h"

GetAllVehicleTypeHandler::GetAllVehicleTypeHandler() {
    data = new DataManager("tracker.db");
}

void GetAllVehicleTypeHandler::listener(http_request request) {
    if (data->connectDb() != DATA_SUCCESS)
        return;
    if (request.method() == methods::GET) {
        handle_get(request);
    } else if (request.method() == methods::PUT) {
        handle_put(request);
    } else if (request.method() == methods::POST) {
        handle_post(request);
    } else if (request.method() == methods::DEL) {
        handle_delete(request);
    }
}

void GetAllVehicleTypeHandler::handle_get(http_request request) {
    std::cout << "GET /api/vehicletype/all\n";

    std::vector<VehicleType> lstVehicleType;
    std::map<std::string, std::string> dictionary;
    std::vector<json::value> vVehicleType;

    if (data->GetAllVehicleType(lstVehicleType) != DATA_SUCCESS) {
        request.reply(status_codes::BadRequest, ResultCode::ERROR);
        return;
    }

    for(auto vehicleType : lstVehicleType) {
        dictionary = vehicleType_to_map(vehicleType);
        json::value json;
        for(auto const& p : dictionary) {
            json[p.first] = json::value::string(p.second);
        }
        vVehicleType.push_back(json);
        dictionary.clear();
    }

    json::value answer;
    answer["data"] = json::value::array(vVehicleType);

    request.reply(status_codes::OK, answer);
}

// PUT /api/branch/all
void GetAllVehicleTypeHandler::handle_put(http_request request) {
    std::cout << "PUT /api/vehicletype/all\n";
    request.reply(status_codes::BadRequest, ResultCode::NOT_SUPPORT);
}

// POST /api/branch/all
void GetAllVehicleTypeHandler::handle_post(http_request request) {
    std::cout << "POST /api/vehicletype/all\n";
    request.reply(status_codes::BadRequest, ResultCode::NOT_SUPPORT);
}

// DELETE /api/branch/all
void GetAllVehicleTypeHandler::handle_delete(http_request request) {
    std::cout << "DELETE /api/vehicletype/all\n";
    request.reply(status_codes::BadRequest, ResultCode::NOT_SUPPORT);
}

std::map<utility::string_t,utility::string_t> GetAllVehicleTypeHandler::vehicleType_to_map(VehicleType &vehicleType) {
    std::map<utility::string_t, utility::string_t> dictionary;
    dictionary["Id"] = vehicleType.getId();
    dictionary["Name"] = vehicleType.getName();
    return dictionary;
}