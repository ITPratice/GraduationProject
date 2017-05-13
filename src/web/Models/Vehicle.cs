using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace VehicleTracker.Models
{
    public class Vehicle
    {
        private String numberPlate;
        private String branchId;
        private String hardwareId;
        private String description;
        private String typeId;
        private String userEmail;
        private int deleted;
        private int writeHistory;

        [StringLength(20, ErrorMessage = "Tối đa 20 ký tự")]
        [Required(ErrorMessage = "Không để trống trường này")]
        [DataType(DataType.Text, ErrorMessage = "Dữ liệu phải là Text")]
        public string NumberPlate { get => numberPlate; set => numberPlate = value; }

        public string BranchId { get => branchId; set => branchId = value; }

        public string HardwareId { get => hardwareId; set => hardwareId = value; }

        [StringLength(200, ErrorMessage = "Tối đa 200 ký tự")]
        [Required(ErrorMessage = "Không để trống trường này")]
        [DataType(DataType.Text, ErrorMessage = "Dữ liệu phải là Text")]
        public string Description { get => description; set => description = value; }

        public string TypeId { get => typeId; set => typeId = value; }

        [StringLength(80, ErrorMessage = "Tối đa 80 ký tự")]
        [Required(ErrorMessage = "Không để trống trường này")]
        [DataType(DataType.EmailAddress)]
        [EmailAddress(ErrorMessage = "Dữ liệu phải là Email")]
        public string UserEmail { get => userEmail; set => userEmail = value; }

        public int Deleted { get => deleted; set => deleted = value; }

        public int WriteHistory { get => writeHistory; set => writeHistory = value; }
    }
}
