#include <iostream>
#include <redox.hpp>
#include <string>

#define TILE38_PORT 9851
#define TILE38_HOST "127.0.0.1"

int main(int argc, char* argv[]) {
    redox::Redox rdx;

    // Block until connected, localhost by default
    if(!rdx.connect(TILE38_HOST, TILE38_PORT)) return 1;
    rdx.command<std::string>({"SET", "fleet", "truck", "POINT", "33.32", "115.423"}, [](redox::Command<std::string>& c) {
        if(!c.ok()) return 1;
        std::cout << c.reply() << std::endl;
    });
    rdx.command<std::string>({"GET", "fleet", "truck"}, [](redox::Command<std::string>& c) {
        if(!c.ok()) return 1;
        std::cout << c.reply() << std::endl;
    });
    rdx.wait();
    return 0;
}
