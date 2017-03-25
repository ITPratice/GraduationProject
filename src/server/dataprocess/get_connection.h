#include <iostream>
#include <string>
#include <vector>
#include <redox.hpp>

#include "../libs/json/json.hpp"

class GetConnection {
public:
    GetConnection();
    ~GetConnection();
public:
    static bool get_connection(redox::Redox rdx);
};