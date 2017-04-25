#include "branch_handler.h"

BranchHandler::BranchHandler() {
    data = new DataManager(Constants::DATABASE_PATH);
}

void BranchHandler::listener(http_request request) {
   if (data->connectDb() != DATA_SUCCESS)
        return;
    if(request.method() == methods::GET) {
        handle_get(request);
    } else if(request.method() == methods::PUT) {
        handle_put(request);
    } else if(request.method() == methods::POST) {
        handle_post(request);
    } else if(request.method() == methods::DEL) {
        handle_delete(request);
    } 
}

// GET /api/branch?id={value}
void BranchHandler::handle_get(http_request request) {
    std::cout << "GET /api/branch\n";
    Branch _outBranch;
    auto get_vars = uri::split_query(request.request_uri().query());
    if(get_vars.empty()) {
        request.reply(status_codes::BadRequest, "Query is null");
        return;
    }

    // Get Branch By Id
    auto _id = get_vars.find("id")->second;
    if(data->GetBranchById(_id, _outBranch) != DATA_SUCCESS) {
        request.reply(status_codes::OK, json::value::string("Query Error"));
        return;
    }

    // Set Branch json
    json::value _jValue;
    _jValue["Id"] = json::value::string(_outBranch.getId());
    _jValue["Name"] = json::value::string(_outBranch.getName());

    // Reply to client
    request.reply(status_code::OK, _jValue);
}

void BranchHandler::handle_get(http_request request) {

}

void BranchHandler::handle_get(http_request request) {

}

void BranchHandler::handle_get(http_request request) {

}