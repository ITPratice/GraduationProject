#include <iostream>
#include <string>

#ifndef USER_H
#define USER_H

enum {
    USER_GROUP = 1,
    WAIT_USER_GROUP = 2,
    ADMIN_GROUP = 3,
};

class User {
public:
    User();
    User(std::string _id, std::string _email, std::string _address, std::string _phone, std::string _numberPlate, std::string _password, unsigned char _type);
    User(std::string _id, std::string _email, std::string _password);
    ~User();
private:
    std::string id;
    std::string email;
    std::string address;
    std::string phone_number;
    std::string number_plate;
    std::string password;
    unsigned char type;
public:
    void setId(std::string id_str);
    std::string getId() const;

    void setEmail(std::string email_str);
    std::string getEmail() const;

    void setAddress(std::string address_str);
    std::string getAddress() const;

    void setPhoneNumber(std::string phone_str);
    std::string getPhoneNumber() const;

    void setNumberPlate(std::string _numberPlate);
    std::string getNumberPlate() const;

    void setPassword(std::string pass_str);
    std::string getPassword() const;

    void setType(unsigned char _type);
    unsigned char getType() const;
};

#endif  //USER_H
