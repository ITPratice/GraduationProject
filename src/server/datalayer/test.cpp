#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

#include "../libs/rest/include/cpprest/http_listener.h"
#include "../libs/rest/include/cpprest/json.h"

#include "../ResponseInterface.h"
#include "../RouteMap.h"
#include "../helper/string_helper.h"
#include "../handler/user_handler/get_all_handler.h"

#include "user_location.h"
#include "user.h"
#include "location.h"

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

void handle_get(http_request request);
std::map<std::string, std::string> user_to_map(User &user);
void routingHandler(http_request request);

std::unique_ptr<get_all_handler> user_Handler;

int main()
{
    http_listener listener("http://localhost:3000/");
    listener.support(routingHandler);
    listener.open().wait();
    while(true);

    return 0;
}

void routingHandler(http_request request) {
    utility::string_t routePath = request.relative_uri().path();
    switch(string_helper::hash_str(routePath)) {
        case E_GET_ALL_USER:
        {
            user_Handler = std::unique_ptr<get_all_handler>(new get_all_handler());
            user_Handler->listener(request);
            break;
        }
        case E_GET_ALL_LOCATION:
            request.reply(status_codes::OK, "Test Location Ok !");
            break;
        default:
            break;
    }
}

