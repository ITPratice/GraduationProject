#ifndef BRANCH_H
#define BRANCH_H

#include <string>

class Branch {
public:
    Branch();
    Branch(std::string _name);
    ~Branch();
private:
    int id;
    std::string name;
public:
    int getId();

    void setName(std::string _name);
    std::string getName();
};

#endif  // TRACKING_H