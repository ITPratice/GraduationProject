#include "../stdafx.h"
#include "../../datalayer/data_manager.h"
#include "../../datalayer/vehicle.h"
#include "../../ResponseInterface.h"

#ifndef WRITE_HISTORY_HANDLER_H
#define WRITE_HISTORY_HANDLER_H

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

class WriteHistoryHandler {
public:
    WriteHistoryHandler();
    void listener(http_request request);
private:
    void handle_get(http_request request);
    void handle_put(http_request request);
    void handle_post(http_request request);
    void handle_delete(http_request request);
private:
    DataManager *data;
};

#endif  // WRITE_HISTORY_HANDLER_H