#ifndef STDAFX_H
#define STDAFX_H

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <ctime>

#include <cpprest/json.h>
#include <cpprest/http_listener.h>
#include <cpprest/uri.h>

#include "stdafx.h"

#include "handler/user/user_handler.h"
#include "handler/user/all_user_handler.h"
#include "handler/user/login_handler.h"
#include "handler/user/login_admin_handler.h"
#include "handler/user/active_user_handler.h"
#include "handler/user/first_handler.h"

#include "handler/location/location_handler.h"
#include "handler/location/current_location_handler.h"

#include "handler/branch/branch_handler.h"

#include "handler/vehicle/vehicle_handler.h"
#include "handler/vehicle/vehicleplate_byuser_handler.h"
#include "handler/vehicle_type/vehicle_type_handler.h"

#include "handler/current_time/current_time_handler.h"
#include "handler/arduino/location.h"


#endif