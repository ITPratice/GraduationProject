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
#include "../handler/location_handler/location_time.h"
#include "../handler/login_handler/login_handler.h"
#include "../handler/tracking_handler/tracking_handler.h"

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

void routingHandler(http_request request);

std::unique_ptr<get_all_handler> a_user_Handler;
std::unique_ptr<login_handler> u_Login_Handler;
std::unique_ptr<tracking_handler> t_Hanlder;

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
            a_user_Handler = std::unique_ptr<get_all_handler>(new get_all_handler());
            a_user_Handler->listener(request);
            break;
        case E_GET_ALL_LOCATION:
            request.reply(status_codes::OK, "Test Location Ok !");
            break;
        // case E_GET_LOCATION_BY_TIME:
        //     t_Location_Handler = std::unique_ptr<location_time>(new location_time());
        //     t_Location_Handler->ltListener(request);
        //     break;
        case E_CHECK_LOGIN:
            u_Login_Handler = std::unique_ptr<login_handler>(new login_handler());
            u_Login_Handler->listener(request);
            break;
        case E_TRACKING:
            t_Hanlder = std::unique_ptr<tracking_handler>(new tracking_handler());
            t_Hanlder->listener(request);
            break;
        default:
            break;
    }
}

