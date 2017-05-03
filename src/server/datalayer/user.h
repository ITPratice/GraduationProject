#include <iostream>
#include <string>

#ifndef USER_H
#define USER_H

class User {
public:
    User();
    User(std::string _email, std::string _uName, std::string _addr, std::string _phone, std::string _fullName, std::string _pass, int role, int first);
    ~User();
private:
    std::string email;
    std::string uName;
    std::string address;
    std::string phone_number;
    std::string full_name;
    std::string password;
    int role;
    int first;
public:
    void setEmail(std::string email_str);
    std::string getEmail();

    void setUsername(std::string _uName);
    std::string getUsername();

    void setAddress(std::string address_str);
    std::string getAddress();

    void setPhoneNumber(std::string phone_str);
    std::string getPhoneNumber();

    void setFullname(std::string _fName);
    std::string getFullname();

    void setPassword(std::string pass_str);
    std::string getPassword();

    void setRole(int _role);
    int getRole();

    void setFirst(int _first);
    int getFirst();
};

#endif  //USER_H
