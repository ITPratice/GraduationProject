#include "branch.h"

Branch::Branch() {
    name = "";
}

Branch::Branch(std::string _name) {
    name = _name;
}

Branch::~Branch() { }

void Branch::setName(std::string _name) {
    name = _name;
}

std::string Branch::getName() {
    return name;
}