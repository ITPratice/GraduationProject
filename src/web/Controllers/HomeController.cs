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
            return RedirectToAction("Index", "Vehicle");
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
            using (var client = new HttpClient())
            {
                try
                {
                    String _result = await UserVM.RegistrationAsync(client, user);
                    if (_result.Equals(ResultCode.DONE))
                    {
                        return RedirectToAction("RegVehicle", "Home");
                    }
                    else
                    {
                        return BadRequest(Lang.LANG_SELECT_PROBLEM);
                    }
                }
                catch(Exception)
                {
                    return BadRequest(Lang.LANG_CONNECTION_PROBLEM);
                }
            }
        }

        [HttpGet]
        public IActionResult RegVehicle()
        {
            return View();
        }

        [HttpPost]
        public async Task<IActionResult> RegVehicle(Vehicle vehicle)
        {
            using (var client = new HttpClient())
            {
                try
                {
                    vehicle.Deleted = 0;
                    vehicle.WriteHistory = 0;
                    String _result = await VehicleVM.InsertVehicleAsync(client, vehicle);
                    if (_result.Equals(ResultCode.DONE))
                    {
                        return RedirectToAction("RegVehicle", "Home");
                    }
                    else
                    {
                        return BadRequest(Lang.LANG_SELECT_PROBLEM);
                    }
                }
                catch(Exception)
                {
                    return BadRequest(Lang.LANG_CONNECTION_PROBLEM);
                }
            }
        }
    }
}