using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
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
        private String passWordConfirm;
        private String phoneNumber;
        private String userName;
        private int role;
        private int first;

        [StringLength(100, ErrorMessage = "Tối đa 100 ký tự")]
        [Required(ErrorMessage = "Không để trống trường này")]
        [DataType(DataType.Text, ErrorMessage = "Dữ liệu phải là Text")]
        public string Address { get => address; set => address = value; }

        [StringLength(80, ErrorMessage = "Tối đa 80 ký tự")]
        [Required(ErrorMessage = "Không để trống trường này")]
        [DataType(DataType.EmailAddress)]
        [EmailAddress(ErrorMessage = "Dữ liệu phải là Email")]
        public string Email { get => email; set => email = value; }

        [StringLength(100, ErrorMessage = "Tối đa 100 ký tự")]
        [Required(ErrorMessage = "Không để trống trường này")]
        [DataType(DataType.Text, ErrorMessage = "Dữ liệu phải là Text")]
        public string FullName { get => fullName; set => fullName = value; }

        [StringLength(20, ErrorMessage = "Tối đa 20 ký tự")]
        [Required(ErrorMessage = "Không để trống trường này")]
        [DataType(DataType.Password)]
        public string PassWord { get => passWord; set => passWord = value; }

        public string PassWordConfirm { get => passWordConfirm; set => passWordConfirm = value; }

        [StringLength(20, ErrorMessage = "Tối đa 20 ký tự")]
        [Required(ErrorMessage = "Không để trống trường này")]
        [DataType(DataType.PhoneNumber, ErrorMessage = "Không đúng số điện thoại")]
        public string PhoneNumber { get => phoneNumber; set => phoneNumber = value; }

        [StringLength(20, ErrorMessage = "Tối đa 20 ký tự")]
        [Required(ErrorMessage = "Không để trống trường này")]
        [DataType(DataType.Text, ErrorMessage = "Dữ liệu phải là Text")]
        public string UserName { get => userName; set => userName = value; }

        public int Role { get => role; set => role = value; }
        public int First { get => first; set => first = value; }
    }
}
