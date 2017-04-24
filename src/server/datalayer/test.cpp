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

    VehicleType vt("TYPE_1", "test_name");
    data.InsertVehicleType(vt);

    Branch br("BRAN_1", "Branch 1");
    data.InsertBranch(br);

    Vehicle v("29V5-4628", "BRAN_1", "HWD_1", "Test Description", "TYPE_1", "cuong@gmail.com");
    data.InsertVehicle(v);

    Location lc("012.36", "56.789", "29V5-4628");
    data.InsertLocation(lc);
    // lc.setLatitude("987.65");
    // data.UpdateLocation(lc);
    // data.DeleteLocation(lc);

    History his("29V5-4628", 2, "date", "sTime", "_eTime");
    data.InsertHistory(his);
    his.setDate("Date_1");
    data.UpdateHistory(his);
    return 0;
}