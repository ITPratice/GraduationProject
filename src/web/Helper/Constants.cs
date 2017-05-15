using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace VehicleTracker.Helper
{
    public class Constants
    {
        // Api End Point
        public static String API_BASE_URL               = "http://52.221.199.175:3000/";
        public static String API_GET_ALL_USER           = "api/user/all";
        public static String API_GET_ALL_USER_ACTIVE    = "api/user/active";
        public static String API_GET_ALL_BRANCH         = "api/branch/all";
        public static String API_GET_ALL_VEHICLE_TYPE   = "api/vehicletype/all";
        public static String API_GET_ALL_VEHICLE        = "api/vehicle/all";
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

    public class Lang
    {
        public static String LANG_CONNECTION_PROBLEM    = "Connection has problem";
        public static String LANG_INSERT_PROBLEM        = "Insert Object Fail";
        public static String LANG_UPDATE_PROBLEM        = "Update Object Fail";
        public static String LANG_DELETE_PROBLEM        = "Delete Object Fail";
        public static String LANG_SELECT_PROBLEM        = "Select Object Fail";

        // 
        public static String LANG_EMAIL_NOT_FOUND   = "Email not found";
    }
}
