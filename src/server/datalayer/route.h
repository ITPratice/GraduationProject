#ifndef ROUTE_H
#define ROUTE_H

#include <string>

class Route {
public:
    Route();
    Route(std::string _nPalte, int _location_id, std::string _sDate, std::string _sTime, std::string _eDate, std::string _eTime);
    ~Route();
private:
    std::string number_plate;
    int location_id;
    std::string start_date;
    std::string start_time;
    std::string end_date;
    std::string end_time;
public:
    void setNumberPlate(std::string _nPlate);
    std::string getNumberPlate();

    void setLocationId(int _location_id);
    int getLocationId();

    void setStartDate(std::string _sDate);
    std::string getStartDate();

    void setStartTime(std::string _sTime);
    std::string getStartTime();

    void setEndDate(std::string _eDate);
    std::string getEndDate();

    void setEndTime(std::string _eTime);
    std::string getEndTime();
};

#endif  // TRACKING_H