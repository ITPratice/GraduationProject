#include "vehicleplate_byuser_handler.h"

VehiclePlateByUserHandler::VehiclePlateByUserHandler() {
    data = new DataManager("tracker.db");
}

void VehiclePlateByUserHandler::listener(http_request request) {
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

// GET /api/vehicle?email=
void VehiclePlateByUserHandler::handle_get(http_request request) {
    std::cout << "GET /api/vehicle/user?email={email}\n";
    std::vector<std::string> lstPlate;
    std::vector<json::value> vPlate;

    auto get_vars = uri::split_query(request.request_uri().query());
    if (get_vars.size() != 1) {
        request.reply(status_codes::BadRequest, ResultCode::URL_INVALID);
        return;
    }

    // Get Email value
    auto _email = uri::decode(get_vars.find("email")->second);
    if(data->GetVehicleNumberByUser(_email, lstPlate) != DATA_SUCCESS) {
        request.reply(status_codes::BadRequest, ResultCode::ERROR);
        return;
    }

    for(auto _plate : lstPlate) {
        json::value json;
        json["Plate"] = json::value::string(_plate);
        vPlate.push_back(json);
    }

    json::value answer;
    answer["data"] = json::value::array(vPlate);

    request.reply(status_codes::OK, answer);
}

void VehiclePlateByUserHandler::handle_put(http_request request) {
    request.reply(status_codes::BadRequest, ResultCode::NOT_SUPPORT);
}

void VehiclePlateByUserHandler::handle_post(http_request request) {
    request.reply(status_codes::BadRequest, ResultCode::NOT_SUPPORT);
}

void VehiclePlateByUserHandler::handle_delete(http_request request) {
    request.reply(status_codes::BadRequest, ResultCode::NOT_SUPPORT);
}

