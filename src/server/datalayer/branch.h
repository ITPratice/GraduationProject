#ifndef BRANCH_H
#define BRANCH_H

#include <string>

class Branch {
public:
    Branch();
    Branch(std::string _id, std::string _name);
    ~Branch();
private:
    std::string id;
    std::string name;
public:
    void setId(std::string _id);
    std::string getId();

    void setName(std::string _name);
    std::string getName();
};

#endif  // TRACKING_H