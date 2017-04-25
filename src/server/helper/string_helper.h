#include "../RouteMap.h"

#define API_USER "/api/user"
#define API_LOCATION "/api/location"
#define API_BRANCH "/api/branch"
#define API_VEHICLE "/api/vehicle"
#define API_VEHICLE_TYPE "/api/vehicletype"

class string_helper {
public:
    static RouteMapCode hash_str(std::string &str);
};

inline RouteMapCode string_helper::hash_str(std::string &in_str) {
    if(in_str == API_USER) return ROUTE_USER;
    else if(in_str == API_LOCATION) return ROUTE_LOCATION;
    else if(in_str == API_BRANCH) return ROUTE_BRANCH;
    else if(in_str == API_VEHICLE) return ROUTE_VEHICLE;
    else if(in_str == API_VEHICLE_TYPE) return ROUTE_VEHICLE_TYPE;
    else return ROUTE_FAILED;
}