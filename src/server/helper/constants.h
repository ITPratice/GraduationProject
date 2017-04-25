#include <string>
#include <iostream>

class Constants {
public:
    static std::string DATABASE_PATH;
};

inline std::string DATABASE_PATH = "tracker.db";