#include "user.h"
#include "../stdafx.h"

User::User() {
    id = "";
    email = "";
    address = "";
    phone_number = "";
    number_plate = "";
    password = "";
    type = USER_GROUP;
}

User::User(std::string _id, std::string _email, std::string _address, std::string _phone, std::string _numberPlate, std::string _password, BYTE _type) {
    id = _id;
    email = _email;
    address = _address;
    phone_number = _phone;
    number_plate = _numberPlate;
    password = _password;
    type = _type;
}

User::User(std::string _id, std::string _email, std::string _password) {
    id = _id;
    email = _email;
    address = "";
    phone_number = "";
    number_plate = "";
    password = _password;
    type = USER_GROUP;
}

User::~User() {}

void User::setId(std::string id_str) {
    id = id_str;
}

std::string User::getId() const {
    return id;
}

void User::setEmail(std::string email_str) {
    email = email_str;
}

std::string User::getEmail() const {
    return email;
}

void User::setAddress(std::string address_str) {
    address = address_str;
}

std::string User::getAddress() const {
    return address;
}

void User::setPhoneNumber(std::string phone_str) {
    phone_number = phone_str;
}

std::string User::getPhoneNumber() const {
    return phone_number;
}

void User::setNumberPlate(std::string _numberPlate) {
    number_plate = _numberPlate;
}

std::string User::getNumberPlate() const {
    return number_plate;
}

void User::setPassword(std::string pass_str) {
    password = pass_str;
}

std::string User::getPassword() const {
    return password;
}

void User::setType(BYTE _type) {
    type = _type;
}

BYTE User::getType() const {
    return type;
}
