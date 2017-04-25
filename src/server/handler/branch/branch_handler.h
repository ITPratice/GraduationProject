#include <iostream>
#include <map>

#include "../stdafx.h"

#ifndef BRANCH_HANDLER_H
#define BRANCH_HANDLER_H

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

class BranchHandler {
public:
    BranchHandler();
    void listener(http_request request);
private:
    void handle_get(http_request request);
    void handle_put(http_request request);
    void handle_post(http_request request);
    void handle_delete(http_request request);
private:
    DataManager *data;
};

#endif  // BRANCH_HANDLER_H