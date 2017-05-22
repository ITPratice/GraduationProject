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
using Microsoft.AspNetCore.Http;

namespace VehicleTracker.Controllers
{
    public class HomeController : Controller
    {
        public IActionResult Index()
        {
            if (HttpContext.Session.GetString("Admin") == null || HttpContext.Session.GetString("Admin") == String.Empty)
            {
                return RedirectToAction("Login", "Admin");
            }
            else
            {
                return RedirectToAction("Index", "Vehicle");
            }
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
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Registration(User user)
        {
            if (ModelState.IsValid)
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
                    catch (Exception)
                    {
                        return BadRequest(Lang.LANG_CONNECTION_PROBLEM);
                    }
                }
            }
            return View();
        }

        [HttpGet]
        public IActionResult RegVehicle()
        {
            return View();
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> RegVehicle(Vehicle vehicle)
        {
            if (ModelState.IsValid)
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
                    catch (Exception)
                    {
                        return BadRequest(Lang.LANG_CONNECTION_PROBLEM);
                    }
                }
            }
            return View();
        }
    }
}