#include "branch.h"

Branch::Branch() {
    name = "";
}

Branch::Branch(std::string _name) {
    name = _name;
}

Branch::~Branch() { }

int Branch::getId() {
    return id;
}

void Branch::setName(std::string _name) {
    name = _name;
}

std::string Branch::getName() {
    return name;
}