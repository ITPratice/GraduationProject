using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using System.Net;
using System.IO;
using System.Net.Http;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using VehicleTracker.Models;
using VehicleTracker.Helper;
using VehicleTracker.ViewModel;

namespace VehicleTracker.Controllers
{
    public class HomeController : Controller
    {
        public IActionResult Index()
        {
            return View();
        }

        public IActionResult Error()
        {
            return View();
        }

        [HttpGet]
        public IActionResult Registration()
        {
            return View();
        }

        [HttpPost]
        public async Task<IActionResult> Registration(User user)
        {
            user.Role = 2;
            user.First = 1;
            String _result = await UserVM.Registration(user);
            if(_result.Equals("\"OK\""))
            {
                return RedirectToAction("RegVehicle", "Home");
            }
            else
            {
                return (BadRequest("Fail"));
            }
        }

        [HttpGet]
        public IActionResult RegVehicle()
        {
            return View();
        }
    }
}