#include <iostream>
#include <redox.hpp>
#include <string>
#include <fstream>
#include <vector>

#include "json/json.hpp"

// for convenience
using json = nlohmann::json;

#define TILE38_PORT 9851
#define TILE38_HOST "127.0.0.1"

int main(int argc, char* argv[]) {
    redox::Redox rdx;

    if(!rdx.connect(TILE38_HOST, TILE38_PORT)) return 1;

    rdx.command<std::string>({"NEARBY", "fleet", "FENCE", "POINT", "33.01", "-115.05", "6000"}, [](redox::Command<std::string>& c) {
        if(!c.ok()) return 1;
        std::cout << c.reply() << std::endl;
    });

    // rdx.command<std::string>({"SET", "fleet", "bob", "POINT", "33.01", "-115.01"}, [](redox::Command<std::string>& c) {
    //     if(!c.ok()) return 1;
    // });

    // rdx.command<std::string>({"SET", "fleet", "bob", "POINT", "33.01", "-115.02"}, [](redox::Command<std::string>& c) {
    //     if(!c.ok()) return 1;
    // });

    // rdx.command<std::string>({"GET", "fleet", "truck"}, [](redox::Command<std::string>& c) {
    //     json jArray;
    //     if(!c.ok()) return 1;
    //     auto j3 = json::parse(c.reply());
    //     auto j4 = j3["coordinates"].get<std::vector<float>>();
    //     std::cout << j3 << std::endl;
    //     for(auto i : j4) {
    //         std::cout << i << std::endl;
    //     }
    // });
    rdx.wait();

    return 0;
}

bool SetLocation(redox::Redox rdx, float latPoint, float lonPoint) {
    
}


