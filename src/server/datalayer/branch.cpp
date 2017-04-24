#include "branch.h"

Branch::Branch() {
    id = "";
    name = "";
}

Branch::Branch(std::string _id, std::string _name) {
    id = _id;
    name = _name;
}

Branch::~Branch() { }

void Branch::setId(std::string _id) {
    id = _id;
}

std::string Branch::getId() {
    return id;
}

void Branch::setName(std::string _name) {
    name = _name;
}

std::string Branch::getName() {
    return name;
}