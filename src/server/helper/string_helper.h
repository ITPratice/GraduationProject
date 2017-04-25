#include "../RouteMap.h"

#define API_USER "/api/user"
#define API_LOCATION "api/location"

class string_helper {
public:
    static RouteMapCode hash_str(std::string &str);
};

inline RouteMapCode string_helper::hash_str(std::string &in_str) {
    if(in_str == API_USER) return ROUTE_USER;
    if(in_str == API_LOCATION) return ROUTE_LOCATION;
}