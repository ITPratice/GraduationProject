using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace VehicleTracker.Helper
{
    public class Constants
    {
        // Api Url
        public static String API_BASE_URL               = "http://52.221.199.175:3000/";
        public static String API_GET_ALL_USER           = "api/user/all";
        public static String API_GET_ALL_USER_ACTIVE    = "api/user/active";
        public static String API_GET_ALL_BRANCH         = "api/branch/all";
        public static String API_GET_ALL_VEHICLE_TYPE   = "api/vehicletype/all";
    }

    public class ResultCode
    {
        public static String DONE               = "1";
        public static String URL_INVALID        = "2";
        public static String ERROR              = "3";
        public static String UNKNOWN            = "4";
        public static String NOT_SUPPORT        = "5";
        public static String FIRST_LOGIN        = "6";
        public static String NOT_FIRST_LOGIN    = "7";
    }
}
