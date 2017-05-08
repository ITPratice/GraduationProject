#include "../../handler/stdafx.h"
#include "../../handler/user_handler/user_handler.h"

#define PORT_NUMBER "5000"
#define HOST_NAME "http://localhost:"

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;

std::unique_ptr<handler> g_httpHandler;

void on_init(const utility::string_t &address);
void on_shutdown();

void on_init(const utility::string_t &address) {
    uri_builder _uri(addr);
    auto _addr = _uri.to_uri().to_string();
    g_httpHandler = std::unique_ptr<user_handler>(new user_handler(_addr));
    g_httpHandler->open().wait();
    return;
}

void on_shutdown() {
    g_httpHandler->close().wait();
    return;
}

int main(int argc, char *argv[]) {
    utility::string_t port = "";
    if(argc >= 2) {
        port = argv[1];
    } else {
        port = PORT_NUMBER;
    }

    utility::string_t addr = HOST_NAME;
    addr.append(port);

    on_init(addr);
    std::cout << "ENTER to exit." << std::endl;
    
    std::string line;
    std::getline(std::cin, line);

    on_shutdown();
    return 0;
}

