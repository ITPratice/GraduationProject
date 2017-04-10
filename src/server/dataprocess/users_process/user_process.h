#include <iostream>
#include <string>

#include "../data_manager.h"
#include "../../datalayer/user.h"

class user_process {
public:
    user_process();
    ~user_process();
public:
    void up_insert(User &user);
    void up_update(User &user);
    void up_delete(User &user);
public:
    bool is_login(User &user);
};