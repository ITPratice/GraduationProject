#include <iostream>
#include <string>

#include "../ResponseInterface.h"

#include "data_manager.h"
#include "user_location.h"
#include "user.h"
#include "location.h"

int main() {
    DataManager data("test.db");
    if(!data.connectDb() == DATA_SUCCESS) {
        std::cout << "ERROR" << std::endl;
        return 1;
    }

    User user("1", "duvuthacu261@gmail.com", "Hanoi", "01684778056", "123456", "29V5-4628", ADMIN_GROUP);
    if(data.InsertUser(user) != DATA_SUCCESS) {
        std::cout << "EROR" << std::endl;
        return 1;
    } else {
        std::cout << "INSERT SUCCESS" << std::endl;
    }

    user.setEmail("cuongdvt261@gmail.com");
    user.setAddress("VietNam");
    if(data.UpdateUser(user) != DATA_SUCCESS) {
        std::cout << "EROR" << std::endl;
        return 1;
    } else {
        std::cout << "UPDATE SUCCESS" << std::endl;
    }

    if(data.DeleteUser(user) != DATA_SUCCESS) {
        std::cout << "EROR" << std::endl;
        return 1;
    } else {
        std::cout << "DELETE SUCCESS" << std::endl;
    }
    return 0;
}
