#include <string>
#include <iostream>

class Constants {
public:
    static std::string DATABASE_PATH;
    static std::string API_BASE_URL;
};

inline std::string DATABASE_PATH = "tracker.db";
inline std::string API_BASE_URL = "http://0.0.0.0:3000/";