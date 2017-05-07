#include "all_vehicle_handler.h"

GetAllVehicleHandler::GetAllVehicleHandler() {
    data = new DataManager("tracker.db");
}

void GetAllVehicleHandler::listener(http_request request) {
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

// GET /api/vehicle/all
void GetAllVehicleHandler::handle_get(http_request request) {
    std::cout << "GET /api/vehicle/all\n";

    std::vector<Vehicle> lstVehicle;
    std::map<std::string, std::string> dictionary;
    std::vector<json::value> vVehicle;

    if (data->GetAllVehicle(lstVehicle) != DATA_SUCCESS) {
        request.reply(status_codes::BadRequest, ResultCode::ERROR);
        return;
    }

    for(auto vehicle : lstVehicle) {
        dictionary = vehicle_to_map(vehicle);
        json::value json;
        for(auto const& p : dictionary) {
            json[p.first] = json::value::string(p.second);
        }
        vVehicle.push_back(json);
        dictionary.clear();
    }

    json::value answer;
    answer["data"] = json::value::array(vVehicle);

    request.reply(status_codes::OK, answer);
}

// PUT /api/vehicle/all
void GetAllVehicleHandler::handle_put(http_request request) {
    std::cout << "PUT /api/vehicle/all\n";
    request.reply(status_codes::BadRequest, ResultCode::NOT_SUPPORT);
}

// POST /api/vehicle/all
void GetAllVehicleHandler::handle_post(http_request request) {
    std::cout << "POST /api/vehicle/all\n";
    request.reply(status_codes::BadRequest, ResultCode::NOT_SUPPORT);
}

// DELETE /api/vehicle/all
void GetAllVehicleHandler::handle_delete(http_request request) {
    std::cout << "DELETE /api/vehicle/all\n";
    request.reply(status_codes::BadRequest, ResultCode::NOT_SUPPORT);
}

std::map<utility::string_t,utility::string_t> GetAllVehicleHandler::vehicle_to_map(Vehicle &vehicle) {
    std::map<utility::string_t, utility::string_t> dictionary;
    dictionary["NumberPlate"] = vehicle.getNumberPlate();
    dictionary["BranchId"] = vehicle.getBranchId();
    dictionary["HardwareId"] = vehicle.getHardwareId();
    dictionary["Description"] = vehicle.getDescription();
    dictionary["TypeId"] = vehicle.getTypeId();
    dictionary["UserEmail"] = vehicle.getUserEmail();
    dictionary["Deleted"] = std::to_string(vehicle.getDeleted());
    return dictionary;
}