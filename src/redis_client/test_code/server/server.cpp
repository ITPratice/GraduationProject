#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <vector>
#include <iostream>

#include "../socket/socket_exception.h"
#include "../socket/socket.h"
#include "../socket/message.hpp"
#include "../socket/header.hpp"

int server_port = 0;

struct FakeData {
    std::string lat_point;
    std::string lon_point;
};

void *ConnectionHandler(void *thrd_args);
bool ProcessMessage(Message& msg, Socket& socket);

int main(int argc, char **argv) {
    std::cout << "Start connection .." << std::endl;
    if(argc < 2) {
        std::cout << "<server_side> port_no";
        return 1;
    }
    try {
        // Create the socket
        // ServerSocket server(port);
        Socket server;
        server_port = atoi(argv[1]);
        if(!server.create()) {
            throw SocketException("Could not create server socket.");
        }
        if(!server.bind(server_port)) {
            throw SocketException("Could not bind to port.");
        }
        std::cout << "bind port" << std::endl;
        if(!server.listen()) {
            throw SocketException("Could not listen to socket.");
        }
        std::cout << "Waiting for incoming connections..." << std::endl;

        // Waiting connection ..
        while (true) {
            Socket* client_socket = new Socket();
            std::cout << "before accept !" << std::endl;
            // server.accept(new_sock);
            if(!server.accept(*client_socket)) {
                delete client_socket;
                throw SocketException("Could not accept socket.");
            }
            std::cout << "Connection accepted" << std::endl;
            pthread_t sniffer_thread;
            if(pthread_create(&sniffer_thread, NULL, ConnectionHandler, (void*)client_socket) < 0) {
                std::cout << "Could not create thread" << std::endl;
                continue;
            }
            std::cout << "Handler assigned" << std::endl;
        }
    } catch (SocketException &e) {
        std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }
    return 0;
}

void *ConnectionHandler(void *thrd_args) {
    std::cout << "Connection Handler" << std::endl;
    Socket* socket = (Socket*) thrd_args;

    // Receive a msg from client
    try{
        Message recv_msg;
        int readed_size = socket->recv(recv_msg);
        std::cout <<"after call Recv: readed_size = " << readed_size <<std::endl;
        if(readed_size == 0) {
            std::cout << "message = 0" << std::endl;
        } else if(readed_size < 0) {
            throw SocketException("Socket error !");
        } else {
            std::cout << "Receive signal from client" << std::endl;
            if(ProcessMessage(recv_msg, *socket)){
                std::cout << "finish handler connection\n";
            }
        }
    } catch (SocketException &e) {
        std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }
}

bool ProcessMessage(Message& msg, Socket& socket) {
    //bool isFinish = true;
    std::vector<std::string> argv = msg.GetCmdArgs();
    int argc = argv.size();
    std::cout << "abc" << argc << std::endl;
    switch(msg.GetHeader()->GetCommand()) {
    case CMD_SEND_REQUEST:
        std::cout << "Connection Success" << std::endl;
        break;
    default:
        break;
    }
}
