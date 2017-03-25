#include <iostream>
#include <string>

#include "../socket/message.hpp"
#include "../socket/header.hpp"
#include "../socket/socket.h"
#include "../socket/socket_exception.h"

int main(int argc, char **argv){
    if(argc > 3) {
        std::cout << "<client> host port";
        return 1;
    }
    const std::string host = argv[1];
    const int port = atoi(argv[2]);
    Socket socket;
    if(!socket.create()) {
        throw SocketException("Could not create client socket.");
    }
    if(!socket.connect(host, port)) {
        throw SocketException("Could not bind to port.");
    }
    try{
        Message msg(Header(MT_COMMAND, port, 0, 0, CMD_SEND_REQUEST), NULL);
        if(!socket.send(msg)) {
            std::cout << "Connection fail" << std::endl;
        } else {
            std::cout << "Connection success" << std::endl;
        }
    } catch (SocketException &e) {
        std::cout << "Exception was caught:" << e.description() << "\n";
    }
    return 0;
}
