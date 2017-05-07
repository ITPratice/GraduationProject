#include "all_branch_handler.h"

GetAllBranchHandler::GetAllBranchHandler() {
    data = new DataManager("tracker.db");
}

void GetAllBranchHandler::listener(http_request request) {
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

// GET /api/branch/all
void GetAllBranchHandler::handle_get(http_request request) {
    std::cout << "GET /api/branch/all\n";

    std::vector<Branch> lstBranch;
    std::map<std::string, std::string> dictionary;
    std::vector<json::value> vBranch;

    if (data->GetAllBranch(lstBranch) != DATA_SUCCESS) {
        request.reply(status_codes::BadRequest, ResultCode::ERROR);
        return;
    }

    for(auto branch : lstBranch) {
        dictionary = branch_to_map(branch);
        json::value json;
        for(auto const& p : dictionary) {
            json[p.first] = json::value::string(p.second);
        }
        vBranch.push_back(json);
        dictionary.clear();
    }

    json::value answer;
    answer["data"] = json::value::array(vBranch);

    request.reply(status_codes::OK, answer);
}

// PUT /api/branch/all
void GetAllBranchHandler::handle_put(http_request request) {
    std::cout << "PUT /api/branch/all\n";
    request.reply(status_codes::BadRequest, ResultCode::NOT_SUPPORT);
}

// POST /api/branch/all
void GetAllBranchHandler::handle_post(http_request request) {
    std::cout << "POST /api/branch/all\n";
    request.reply(status_codes::BadRequest, ResultCode::NOT_SUPPORT);
}

// DELETE /api/branch/all
void GetAllBranchHandler::handle_delete(http_request request) {
    std::cout << "DELETE /api/branch/all\n";
    request.reply(status_codes::BadRequest, ResultCode::NOT_SUPPORT);
}

std::map<utility::string_t,utility::string_t> GetAllBranchHandler::branch_to_map(Branch &branch) {
    std::map<utility::string_t, utility::string_t> dictionary;
    dictionary["Id"] = branch.getId();
    dictionary["Name"] = branch.getName();
    return dictionary;
}