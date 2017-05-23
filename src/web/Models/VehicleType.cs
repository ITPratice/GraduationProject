using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace VehicleTracker.Models
{
    public class VehicleType
    {
        private String id;
        private String name;

        [StringLength(10, ErrorMessage = "Tối đa 10 ký tự")]
        [Required(ErrorMessage = "Không để trống trường này")]
        public string Id { get => id; set => id = value; }

        [StringLength(100, ErrorMessage = "Tối đa 100 ký tự")]
        [Required(ErrorMessage = "Không để trống trường này")]
        public string Name { get => name; set => name = value; }
    }
}
