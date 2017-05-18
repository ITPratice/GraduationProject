#include "branch_handler.h"

BranchHandler::BranchHandler() {
    data = new DataManager("tracker.db");
}

void BranchHandler::listener(http_request request) {
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

// GET /api/branch?id={value}
void BranchHandler::handle_get(http_request request) {
    std::cout << "GET /api/branch\n";
    Branch _outBranch;
    auto get_vars = uri::split_query(request.request_uri().query());
    if (get_vars.size() != 1) {
        request.reply(status_codes::BadRequest, ResultCode::URL_INVALID);
        return;
    }

    // Get Branch By Id
    auto _id = get_vars.find("id")->second;
    if (data->GetBranchById(_id, _outBranch) != DATA_SUCCESS) {
        request.reply(status_codes::BadRequest, ResultCode::ERROR);
        return;
    }

    // Set Branch json
    json::value _jValue;
    _jValue["Id"] = json::value::string(_outBranch.getId());
    _jValue["Name"] = json::value::string(_outBranch.getName());

    // Reply to client
    request.reply(status_codes::OK, _jValue);
}

// PUT /api/branch
void BranchHandler::handle_put(http_request request) {
    std::cout << "PUT /api/branch\n";

    auto get_vars = uri::split_query(request.request_uri().query());
    if (get_vars.size() != 2) {
        request.reply(status_codes::BadRequest, ResultCode::URL_INVALID);
        return;
    }

    // Get Branch value
    auto _id = uri::decode(get_vars.find("id")->second);
    auto _name = uri::decode(get_vars.find("name")->second);
    Branch _branch(_id, _name);

    // Update Branch
    if (data->UpdateBranch(_branch) == DATA_SUCCESS) {
        request.reply(status_codes::OK, ResultCode::DONE);
    } else {
        request.reply(status_codes::OK, ResultCode::ERROR);
    }
}

// POST /api/branch
void BranchHandler::handle_post(http_request request) {
    std::cout << "POST /api/branch\n";

    auto get_vars = uri::split_query(request.request_uri().query());
    if (get_vars.size() != 2) {
        request.reply(status_codes::BadRequest, ResultCode::URL_INVALID);
        return;
    }

    // Get Branch value
    auto _id = uri::decode(get_vars.find("id")->second);
    auto _name = uri::decode(get_vars.find("name")->second);
    Branch _branch(_id, _name);

    // Update Branch
    if (data->InsertBranch(_branch) == DATA_SUCCESS) {
        request.reply(status_codes::OK, ResultCode::DONE);
    } else {
        request.reply(status_codes::OK, ResultCode::ERROR);
    }
}

// DELETE /api/branch
void BranchHandler::handle_delete(http_request request) {
    std::cout << "DELETE /api/branch\n";

    auto get_vars = uri::split_query(request.request_uri().query());
    if (get_vars.size() != 2) {
        request.reply(status_codes::BadRequest, ResultCode::URL_INVALID);
        return;
    }

    // Get Branch value
    auto _id = uri::decode(get_vars.find("id")->second);
    auto _name = uri::decode(get_vars.find("name")->second);
    Branch _branch(_id, _name);

    // Update Branch
    if (data->DeleteBranch(_branch) == DATA_SUCCESS) {
        request.reply(status_codes::OK, ResultCode::DONE);
    } else {
        request.reply(status_codes::OK, ResultCode::ERROR);
    }
}