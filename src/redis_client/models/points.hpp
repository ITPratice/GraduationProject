#include <iostream>
#include <string>

class Points {
public:
    inline Points() {}
    ~Points();
    Points(std::string lat_point, std::string lon_point);
    std::string get_lat_point();
    void set_lat_point(std::string latPoint);
    std::string get_lon_point();
    void get_lon_point(std::string lonPoint);
private : 
    std::string lat_point;
    std::string lon_point;
};