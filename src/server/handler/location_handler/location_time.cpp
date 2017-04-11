#include "location_time.h"

location_time::location_time() {
    data = new DataManager("test.db");
}

void location_time::ltListener(http_request request) {
    if (data->connectDb() != DATA_SUCCESS)
        return;
    if(request.method() == methods::GET) {
        ltHandle_get(request);
    } else if(request.method() == methods::PUT) {
        ltHandle_put(request);
    } else if(request.method() == methods::POST) {
        ltHandle_post(request);
    } else if(request.method() == methods::DEL) {
        ltHandle_delete(request);
    }
}

// GET /api/user/all
void location_time::ltHandle_get(http_request request) {
    std::cout << "GET /api/location/user\n";
    std::cout << request.relative_uri().query() << std::endl;

    auto get_vars = uri::split_query(request.request_uri().query());
    for(auto const & p : get_vars) {
        std::cout << "First: " << p.first << " Second: " << p.second << std::endl;
    }
}

void location_time::ltHandle_put(http_request request) {
    request.reply(status_codes::OK, "Not support");
}

void location_time::ltHandle_post(http_request request) {
    request.reply(status_codes::OK, "Not support");
}

void location_time::ltHandle_delete(http_request request) {
    request.reply(status_codes::OK, "Not support");
}
