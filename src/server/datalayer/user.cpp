#include "user.h"
#include "../stdafx.h"

User::User() {
    uName = "";
    email = "";
    address = "";
    phone_number = "";
    full_name = "";
    password = "";
    is_confirm = 0;
    type = 4;
}

User::User(std::string _email, std::string _uName, std::string _addr, std::string _phone, std::string _fullName, std::string _pass, int _confirm, int _type) {
    email = _email;
    uName = _uName;
    address = _addr;
    phone_number = _phone;
    full_name = _fullName;
    password = _pass;
    is_confirm = _confirm;
    type = _type;
}

User::~User() {}

void User::setEmail(std::string email_str) {
    email = email_str;
}

std::string User::getEmail(){
    return email;
}

void User::setUsername(std::string _uName) {
    uName = _uName;
}

std::string User::getUsername() {
    return uName;
}

void User::setAddress(std::string address_str) {
    address = address_str;
}

std::string User::getAddress(){
    return address;
}

void User::setPhoneNumber(std::string phone_str) {
    phone_number = phone_str;
}

std::string User::getPhoneNumber(){
    return phone_number;
}

void User::setFullname(std::string _fName) {
    full_name = _fName;
}

std::string User::getFullname(){
    return full_name;
}

void User::setPassword(std::string pass_str) {
    password = pass_str;
}

std::string User::getPassword() {
    return password;
}

void User::setIsConfirm(int _confirm) {
    is_confirm = _confirm;
}

int User::getIsConfirm() {
    return is_confirm;
}

void User::setType(int _type) {
    type = _type;
}

int User::getType() {
    return type;
}
