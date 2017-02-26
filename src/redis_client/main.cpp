#include <iostream>
#include <redox.hpp>
#include <string>

#define TILE38_PORT 9851
#define TILE38_HOST "127.0.0.1"

using namespace std;
using namespace redox;

int main(int argc, char* argv[]) {
    Redox rdx;

    // Block until connected, localhost by default
    if(!rdx.connect(TILE38_HOST, TILE38_PORT)) return 1;
    rdx.command<string>({"SET", "fleet", "truck", "POINT", "33.32", "115.423"}, [](Command<string>& c) {
        if(!c.ok()) return 1;
        std::cout << c.reply() << std::endl;
    });
    rdx.command<string>({"GET", "fleet", "truck"}, [](Command<string>& c) {
        if(!c.ok()) return 1;
        std::cout << c.reply() << std::endl;
    });
    rdx.wait();
    return 0;
}
