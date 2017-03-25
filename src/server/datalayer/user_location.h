#include <string>

#ifndef USER_LOCATION_H
#define USER_LOCATION_H

class UserLocation
{
public:
    UserLocation();
    UserLocation(std::string uId, std::string lId, std::string _time);
    ~UserLocation();
private:
    std::string user_id;
    std::string location_id;
    std::string time;
public:
    void setUserId(std::string uId);
    std::string getUserId() const;

    void setLocationId(std::string lId);
    std::string getLocationId() const;

    void setTime(std::string _time);
    std::string getTime() const;
};

#endif  // USER_LOCATION_H
