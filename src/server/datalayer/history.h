#ifndef HISTORY_H
#define HISTORY_H

#include <string>

class History {
public:
    History();
    History(std::string _nPalte, int _location_id, std::string _date, std::string _sTime, std::string _eTime);
    ~History();
private:
    std::string number_plate;
    int location_id;
    std::string date;
    std::string start_time;
    std::string end_time;
public:
    void setNumberPlate(std::string _nPlate);
    std::string getNumberPlate();

    void setLocationId(int _location_id);
    int getLocationId();

    void setDate(std::string _date);
    std::string getDate();

    void setStartTime(std::string _sTime);
    std::string getStartTime();

    void setEndTime(std::string _eTime);
    std::string getEndTime();
};

#endif  // HISTORY_H