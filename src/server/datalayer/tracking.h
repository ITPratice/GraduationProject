#ifndef TRACKING_H
#define TRACKING_H

#include <string>

class Tracking {
public:
    Tracking();
    Tracking(std::string _date, std::string _time, std::string _lat, std::string _lon, std::string _hId);
    ~Tracking();
private:
    std::string date;
    std::string time;
    std::string latitude;
    std::string longititu;
    std::string hardware_id;
public:
    void setDate(std::string _date);
    std::string getDate();

    void setTime(std::string _time);
    std::string getTime();

    void setLatitude(std::string _lat);
    std::string getLatitude();

    void setLongititu(std::string _lon);
    std::string getLongititu();

    void setHardwareId(std::string _hId);
    std::string getHardwareId();
};

#endif  // TRACKING_H