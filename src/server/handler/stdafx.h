#ifndef STDAFX_H
#define STDAFX_H

#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <fstream>
#include <random>

#include "../libs/rest/include/cpprest/http_listener.h"
#include "../libs/rest/include/cpprest/json.h"
#include "../libs/rest/include/cpprest/uri.h"
#include "../libs/rest/include/cpprest/asyncrt_utils.h"
#include "../libs/rest/include/cpprest/filestream.h"
#include "../libs/rest/include/cpprest/containerstream.h"
#include "../libs/rest/include/cpprest/producerconsumerstream.h"

#include "../datalayer/data_manager.h"
#include "../datalayer/branch.h"
#include "../datalayer/user.h"
#include "../datalayer/location.h"
#include "../datalayer/vehicle.h"
#include "../datalayer/vehicle_type.h"

#include "../ResponseInterface.h"
#include "../helper/constants.h"
#endif // STDAFX_H