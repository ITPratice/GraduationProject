#include "../RouteMap.h"

#define GET_ALL_USER "/api/user/all"
#define GET_ALL_LOCATION "/api/location/all"
#define GET_LOCATION_BY_TIME "/api/location/user"
#define CHECK_LOGIN "/api/login/user"

class string_helper {
public:
    static RouteMapCode hash_str(std::string &str);
};

inline RouteMapCode string_helper::hash_str(std::string &in_str) {
    if(in_str == GET_ALL_USER) return E_GET_ALL_USER;
    if(in_str == GET_ALL_LOCATION) return E_GET_ALL_LOCATION;
    if(in_str == GET_LOCATION_BY_TIME) return E_GET_LOCATION_BY_TIME;
    if(in_str == CHECK_LOGIN) return E_CHECK_LOGIN;
}