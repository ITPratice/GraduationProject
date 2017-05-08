#include "vehicle_type_handler.h"

VehicleTypeHandler::VehicleTypeHandler() {
    data = new DataManager("tracker.db");
}

void VehicleTypeHandler::listener(http_request request) {
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

// GET /api/vehicletype?id
void VehicleTypeHandler::handle_get(http_request request) {
    std::cout << "GET /api/vehicletype?id\n";
    VehicleType _outVehicleType;
    auto get_vars = uri::split_query(request.request_uri().query());
    if (get_vars.size() != 1) {
        request.reply(status_codes::BadRequest, ResultCode::URL_INVALID);
        return;
    }

    // Get vehicle type by id
    auto _id = uri::decode(get_vars.find("id")->second);
    if (data->GetVehicleTypeById(_id, _outVehicleType) != DATA_SUCCESS) {
        request.reply(status_codes::BadRequest, ResultCode::ERROR);
        return;
    }

    // Set User json
    json::value _jValue;
    _jValue["Id"] = json::value::string(_outVehicleType.getId());
    _jValue["Name"] = json::value::string(_outVehicleType.getName());

    request.reply(status_codes::OK, _jValue);
}

// PUT /api/vehicletype
void VehicleTypeHandler::handle_put(http_request request) {
    std::cout << "PUT /api/vehicletype\n";

    auto get_vars = uri::split_query(request.request_uri().query());
    if (get_vars.size() != 2) {
        request.reply(status_codes::BadRequest, ResultCode::URL_INVALID);
        return;
    }

    // Get vehicletype values from query
    auto _id = uri::decode(get_vars.find("id")->second);
    auto _name = uri::decode(get_vars.find("name")->second);
    VehicleType _vType(_id, _name);

    // Update VehicleType
    if (data->UpdateVehicleType(_vType) == DATA_SUCCESS) {
        request.reply(status_codes::OK, ResultCode::DONE);
    } else {
        request.reply(status_codes::BadRequest, ResultCode::ERROR);
    }
}

// POST /api/vehicletype
void VehicleTypeHandler::handle_post(http_request request) {
    std::cout << "POST /api/vehicletype\n";

    auto get_vars = uri::split_query(request.request_uri().query());
    if (get_vars.size() != 2) {
        request.reply(status_codes::BadRequest, ResultCode::URL_INVALID);
        return;
    }

    // Get vehicletype values from query
    auto _id = uri::decode(get_vars.find("id")->second);
    auto _name = uri::decode(get_vars.find("name")->second);
    VehicleType _vType(_id, _name);

    // Insert VehicleType
    if (data->InsertVehicleType(_vType) == DATA_SUCCESS) {
        request.reply(status_codes::OK, ResultCode::DONE);
    } else {
        request.reply(status_codes::BadRequest, ResultCode::ERROR);
    }
}

// DELETE /api/vehicletype
void VehicleTypeHandler::handle_delete(http_request request) {
    std::cout << "DELETE /api/vehicletype\n";

    auto get_vars = uri::split_query(request.request_uri().query());
    if (get_vars.size() != 2) {
        request.reply(status_codes::BadRequest, ResultCode::URL_INVALID);
        return;
    }

    // Get vehicletype values from query
    auto _id = uri::decode(get_vars.find("id")->second);
    auto _name = uri::decode(get_vars.find("name")->second);
    VehicleType _vType(_id, _name);

    // Insert VehicleType
    if (data->DeleteVehicleType(_vType) == DATA_SUCCESS) {
        request.reply(status_codes::OK, ResultCode::DONE);
    } else {
        request.reply(status_codes::BadRequest, ResultCode::ERROR);
    }
}