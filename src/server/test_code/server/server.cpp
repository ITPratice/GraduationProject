#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <vector>
#include <iostream>
//#include <redox.hpp>

#include "../socket/socket_exception.h"
#include "../socket/socket.h"
#include "../socket/message.hpp"
#include "../socket/header.hpp"

#define SIZE_OF_DATA 20
#define CMD_SEPERATOR '#'

int server_port = 0;

void *ConnectionHandler(void *thrd_args);
bool ProcessMessage(char* data, Socket& socket);
std::vector<std::string> GetCmdArgs(char* data);
void Split(const std::string &str, char del, std::vector<std::string> *out);

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
    try {
        char* recv_msg = new char[SIZE_OF_DATA];
        int readed_size = socket->recv(recv_msg, SIZE_OF_DATA);
        std::cout << "Data receive: " << puts(recv_msg) << std::endl;
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

bool ProcessMessage(char* data, Socket& socket) {
    //bool isFinish = true;
    std::vector<std::string> argv = GetCmdArgs(data);
    int argc = argv.size();
    std::cout << "argc = " << argc << std::endl;
    return true;
}

void Split(const std::string &str, char del, std::vector<std::string> *out) {
    std::istringstream ss(str);
    std::string s;
    while (std::getline(ss, s, del)) {
        out->push_back(s);
    }
}

std::vector<std::string> GetCmdArgs(char* data){
    std::cout << "Message::GetCmdArgs ";
    std::vector<std::string> argv;

    char* data_str = new char[SIZE_OF_DATA + 1];
    memcpy(data_str, data, SIZE_OF_DATA);
    data_str[SIZE_OF_DATA] = '\0';
    std::cout <<"m_data:" << data_str << std::endl;

    // Parse args
    std::string _data(data_str);
    Split(_data, CMD_SEPERATOR, &argv);

    std::cout << " argc=" << argv.size() << ":";
    for(unsigned int i = 0; i < argv.size(); i ++){
        std::cout << "Arg[" << i << "] = " << argv[i] << " " << std::endl;
    }

    delete[]data_str;
    return argv;
}

//void connect_to_tile38() {
//    redox::Redox rdx;
//    if(!rdx.connect(TILE38_HOST, TILE38_PORT)) return false;
//    rdx.command<std::string>({"SET", "fleet", "truck", "POINT", "33.32", "115.423"}, [](redox::Command<std::string>& c) {
//        if(!c.ok()) return 1;
//        std::cout << c.reply() << std::endl;
//    });
//    rdx.command<std::string>({"GET", "fleet", "truck"}, [](redox::Command<std::string>& c) {
//        if(!c.ok()) return 1;
//        std::cout << c.reply() << std::endl;
//    });
//    rdx.wait();
//}
