using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace VehicleTracker.Models
{
    public class User
    {
        private String address;
        private String email;
        private String fullName;
        private String passWord;
        private String phoneNumber;
        private String userName;
        private int role;

        public string Address { get => address; set => address = value; }
        public string Email { get => email; set => email = value; }
        public string FullName { get => fullName; set => fullName = value; }
        public string PassWord { get => passWord; set => passWord = value; }
        public string PhoneNumber { get => phoneNumber; set => phoneNumber = value; }
        public string UserName { get => userName; set => userName = value; }
        public int Role { get => role; set => role = value; }
    }
}
