#ifndef TRACKING_H
#define TRACKING_H

#include <string>

class Tracking {
public:
    Tracking();
    Tracking(std::string _lat, std::string _lon);
    ~Tracking();
private:
    int id;
    std::string latitude;
    std::string longititu;
    std::string hardware_id;
public:
    int getId();

    void setLatitude(std::string _lat);
    std::string getLatitude();

    void setLongititu(std::string _lon);
    std::string getLongititu();
};

#endif  // TRACKING_H