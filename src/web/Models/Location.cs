using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace VehicleTracker.Models
{
    public class Location
    {
        private int id;
        private String latitude;
        private String longititu;
        private String numberPlate;
        private String date;
        private String startTime;
        private String endTime;

        public int Id { get => id; set => id = value; }
        public string Latitude { get => latitude; set => latitude = value; }
        public string Longititu { get => longititu; set => longititu = value; }
        public string NumberPlate { get => numberPlate; set => numberPlate = value; }
        public string Date { get => date; set => date = value; }
        public string StartTime { get => startTime; set => startTime = value; }
        public string EndTime { get => endTime; set => endTime = value; }
    }
}
