#include <string>
#include <iostream>

#include "../RouteMap.h"

#define API_USER "/api/user"
#define API_LOCATION "/api/location"
#define API_BRANCH "/api/branch"
#define API_VEHICLE "/api/vehicle"
#define API_VEHICLE_TYPE "/api/vehicletype"
#define API_CURRENT_TIME "/api/time"

class string_helper {
public:
    static RouteMapCode hash_str(std::string &str);
    static std::string replace_in_str(std::string in_str, std::string to_find, int len, std::string to_replace);
    static std::string replace_space(std::string in_str);
};

inline RouteMapCode string_helper::hash_str(std::string &in_str) {
    if (in_str == API_USER) return ROUTE_USER;
    else if (in_str == API_LOCATION) return ROUTE_LOCATION;
    else if (in_str == API_BRANCH) return ROUTE_BRANCH;
    else if (in_str == API_VEHICLE) return ROUTE_VEHICLE;
    else if (in_str == API_VEHICLE_TYPE) return ROUTE_VEHICLE_TYPE;
    else if (in_str == API_CURRENT_TIME) return ROUTE_CURRENT_TIME;
    else return ROUTE_FAILED;
}

inline std::string string_helper::replace_in_str(std::string in_str, std::string to_find, int len, std::string to_replace) {
    std::size_t pos = 0;
    std::string _tmp = in_str;
    for (pos = _tmp.find(to_find); pos != std::string::npos; pos = _tmp.find(to_find, pos)) {
        _tmp.replace(pos, len, to_replace);
    }
    return _tmp;
}


inline std::string string_helper::replace_space(std::string in_str) {
    return replace_in_str(in_str, "%20", 3, " ");
}