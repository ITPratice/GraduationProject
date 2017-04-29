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
    if (get_vars.empty()) {
        request.reply(status_codes::BadRequest, "Query is null");
        return;
    }

    // Get vehicle by NumberPlate
    auto _plate = get_vars.find("plate")->second;
    if (data->GetVehicleByNumberPlate(_plate, _outVehicle) != DATA_SUCCESS) {
        request.reply(status_codes::BadRequest, json::value::string("Query Error"));
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

    // Reply to client
    request.reply(status_codes::OK, _jValue);
}

// PUT /api/vehicle
void VehicleHandler::handle_put(http_request request) {
    std::cout << "PUT /api/vehicle\n";
    auto get_vars = uri::split_query(request.request_uri().query());
    if (get_vars.empty()) {
        request.reply(status_codes::BadRequest, "Query is null");
        return;
    }

    // Get vehicle value from query
    auto _plate = uri::decode(get_vars.find("plate")->second);
    auto _bId = uri::decode(get_vars.find("brand")->second);
    auto _hId = uri::decode(get_vars.find("hardware")->second);
    auto _des = uri::decode(get_vars.find("description")->second);
    auto _type = uri::decode(get_vars.find("type")->second);
    auto _email = uri::decode(get_vars.find("email")->second);
    Vehicle _vehicle(_plate, _bId, _hId, _des, _type, _email);

    // Update vehicle
    if (data->UpdateVehicle(_vehicle) == DATA_SUCCESS) {
        request.reply(status_codes::OK, json::value::string("OK"));
    } else {
        request.reply(status_codes::BadRequest, json::value::string("ERROR"));
    }
}

// POST /api/vehicle
void VehicleHandler::handle_post(http_request request) {
    std::cout << "POST /api/vehicle\n";
    auto get_vars = uri::split_query(request.request_uri().query());
    if (get_vars.empty()) {
        request.reply(status_codes::BadRequest, "Query is null");
        return;
    }

    // Get vehicle value from query
    auto _plate = uri::decode(get_vars.find("plate")->second);
    auto _bId = uri::decode(get_vars.find("brand")->second);
    auto _hId = uri::decode(get_vars.find("hardware")->second);
    auto _des = uri::decode(get_vars.find("description")->second);
    auto _type = uri::decode(get_vars.find("type")->second);
    auto _email = uri::decode(get_vars.find("email")->second);
    Vehicle _vehicle(_plate, _bId, _hId, _des, _type, _email);

    // Update vehicle
    if (data->InsertVehicle(_vehicle) == DATA_SUCCESS) {
        request.reply(status_codes::OK, json::value::string("OK"));
    } else {
        request.reply(status_codes::BadRequest, json::value::string("ERROR"));
    }
}

// DELETE /api/vehicle
void VehicleHandler::handle_delete(http_request request) {
    std::cout << "DELETE /api/vehicle\n";
    auto get_vars = uri::split_query(request.request_uri().query());
    if (get_vars.empty()) {
        request.reply(status_codes::BadRequest, "Query is null");
        return;
    }

    // Get vehicle value from query
    auto _plate = uri::decode(get_vars.find("plate")->second);
    auto _bId = uri::decode(get_vars.find("brand")->second);
    auto _hId = uri::decode(get_vars.find("hardware")->second);
    auto _des = uri::decode(get_vars.find("description")->second);
    auto _type = uri::decode(get_vars.find("type")->second);
    auto _email = uri::decode(get_vars.find("email")->second);
    Vehicle _vehicle(_plate, _bId, _hId, _des, _type, _email);

    // Update vehicle
    if (data->DeleteVehicle(_vehicle) == DATA_SUCCESS) {
        request.reply(status_codes::OK, json::value::string("OK"));
    } else {
        request.reply(status_codes::BadRequest, json::value::string("ERROR"));
    }
}