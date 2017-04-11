#include "../RouteMap.h"

#define GET_ALL_USER "/api/user/all"
#define GET_ALL_LOCATION "/api/location/all"

class string_helper {
public:
    static RouteMapCode hash_str(std::string &str);
};

inline RouteMapCode string_helper::hash_str(std::string &in_str) {
    if(in_str == GET_ALL_USER) return E_GET_ALL_USER;
    if(in_str == GET_ALL_LOCATION) return E_GET_ALL_LOCATION;
}