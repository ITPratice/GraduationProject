#include <iostream>
#include <string>

#include "data_manager.h"
#include "user.h"
#include "../ResponseInterface.h"

using namespace std;

int main() {
    DataManager data("test.db");
    data.connectDb();

    User user("cuong@gmail.com", "cuong", "hanoi", "0123456789", "duong", "123456", 1);
    data.InsertUser(user);

    return 0;
}