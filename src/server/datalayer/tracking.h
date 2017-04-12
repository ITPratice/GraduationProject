#include <string>

class Tracking {
public:
    Tracking();
    Tracking(std::string _date, std::string _time, std::string _lat, std::string _lon, std::string _vNumber, std::string _hId);
    ~Tracking();
private:
    std::string tracking_date;
    std::string tracking_time;
    std::string lat_point;
    std::string lon_point;
    std::string vehicle_number;
    std::string hardware_id;
public:
    void setTrackingDate(std::string _date);
    std::string getTrackingDate();

    void setTrackingTime(std::string _time);
    std::string getTrackingTime();

    void setLatPoint(std::string _lat);
    std::string getLatPoint();

    void setLonPoint(std::string _lon);
    std::string getLonPoint();

    void setVehicleNumber(std::string _vNumber);
    std::string getVehicleNumber();

    void setHardwareId(std::string _hId);
    std::string getHardwareId();
};