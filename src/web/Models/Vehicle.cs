using System;
using System.Collections.Generic;
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

        public string NumberPlate { get => numberPlate; set => numberPlate = value; }
        public string BranchId { get => branchId; set => branchId = value; }
        public string HardwareId { get => hardwareId; set => hardwareId = value; }
        public string Description { get => description; set => description = value; }
        public string TypeId { get => typeId; set => typeId = value; }
        public string UserEmail { get => userEmail; set => userEmail = value; }
        public int Deleted { get => deleted; set => deleted = value; }
        public int WriteHistory { get => writeHistory; set => writeHistory = value; }
    }
}
