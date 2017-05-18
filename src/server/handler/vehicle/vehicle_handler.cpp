#include "vehicle_handler.h"

VehicleHandler::VehicleHandler() {
    data = new DataManager("tracker.db");
}

void VehicleHandler::listener(http_request request) {
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

// GET /api/vehicle?plate={}
void VehicleHandler::handle_get(http_request request) {
    std::cout << "GET /api/vehicle\n";
    Vehicle _outVehicle;
    auto get_vars = uri::split_query(request.request_uri().query());
    if (get_vars.size() != 1) {
        request.reply(status_codes::BadRequest, ResultCode::URL_INVALID);
        return;
    }

    // Get vehicle by NumberPlate
    auto _plate = get_vars.find("plate")->second;
    if (data->GetVehicleByNumberPlate(_plate, _outVehicle) != DATA_SUCCESS) {
        request.reply(status_codes::BadRequest, ResultCode::ERROR);
        return;
    }

    // Set Vehicle json
    json::value _jValue;
    _jValue["NumberPlate"] = json::value::string(_outVehicle.getNumberPlate());
    _jValue["BranchId"] = json::value::string(_outVehicle.getBranchId());
    _jValue["HardwareId"] = json::value::string(_outVehicle.getHardwareId());
    _jValue["Description"] = json::value::string(_outVehicle.getDescription());
    _jValue["TypeId"] = json::value::string(_outVehicle.getTypeId());
    _jValue["UserEmail"] = json::value::string(_outVehicle.getUserEmail());
    _jValue["Deleted"] = json::value::number(_outVehicle.getDeleted());
    _jValue["WriteHistory"] = json::value::number(_outVehicle.getWriteHistory());

    // Reply to client
    request.reply(status_codes::OK, _jValue);
}

// PUT /api/vehicle
void VehicleHandler::handle_put(http_request request) {
    std::cout << "PUT /api/vehicle\n";
    auto get_vars = uri::split_query(request.request_uri().query());
    if (get_vars.size() != 8) {
        request.reply(status_codes::BadRequest, ResultCode::URL_INVALID);
        return;
    }

    // Get vehicle value from query
    auto _plate = uri::decode(get_vars.find("plate")->second);
    auto _bId = uri::decode(get_vars.find("brand")->second);
    auto _hId = uri::decode(get_vars.find("hardware")->second);
    auto _des = uri::decode(get_vars.find("description")->second);
    auto _type = uri::decode(get_vars.find("type")->second);
    auto _email = uri::decode(get_vars.find("email")->second);
    auto _deleted = uri::decode(get_vars.find("deleted")->second);
    auto _write = uri::decode(get_vars.find("write")->second);
    Vehicle _vehicle(_plate, _bId, _hId, _des, _type, _email, stoi(_deleted), stoi(_write));

    // Update vehicle
    if (data->UpdateVehicle(_vehicle) == DATA_SUCCESS) {
        request.reply(status_codes::OK, ResultCode::DONE);
    } else {
        request.reply(status_codes::OK, ResultCode::ERROR);
    }
}

// POST /api/vehicle
void VehicleHandler::handle_post(http_request request) {
    std::cout << "POST /api/vehicle\n";
    auto get_vars = uri::split_query(request.request_uri().query());
    if (get_vars.size() != 8) {
        request.reply(status_codes::BadRequest, ResultCode::URL_INVALID);
        return;
    }

    // Get vehicle value from query
    auto _plate = uri::decode(get_vars.find("plate")->second);
    auto _bId = uri::decode(get_vars.find("brand")->second);
    auto _hId = uri::decode(get_vars.find("hardware")->second);
    auto _des = uri::decode(get_vars.find("description")->second);
    auto _type = uri::decode(get_vars.find("type")->second);
    auto _email = uri::decode(get_vars.find("email")->second);
    auto _deleted = uri::decode(get_vars.find("deleted")->second);
    auto _write = uri::decode(get_vars.find("write")->second);
    Vehicle _vehicle(_plate, _bId, _hId, _des, _type, _email, stoi(_deleted), stoi(_write));

    // Update vehicle
    if (data->InsertVehicle(_vehicle) == DATA_SUCCESS) {
        request.reply(status_codes::OK, ResultCode::DONE);
    } else {
        request.reply(status_codes::OK, ResultCode::ERROR);
    }
}

// DELETE /api/vehicle
void VehicleHandler::handle_delete(http_request request) {
    std::cout << "DELETE /api/vehicle\n";
    auto get_vars = uri::split_query(request.request_uri().query());
    if (get_vars.size() != 1) {
        request.reply(status_codes::BadRequest, ResultCode::URL_INVALID);
        return;
    }
    // Get vehicle value from query
    auto _plate = uri::decode(get_vars.find("plate")->second);
    
    // Update vehicle
    if (data->BanVehicle(_plate) == DATA_SUCCESS) {
        request.reply(status_codes::OK, ResultCode::DONE);
    } else {
        request.reply(status_codes::OK, ResultCode::ERROR);
    }
}