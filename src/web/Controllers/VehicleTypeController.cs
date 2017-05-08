using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using VehicleTracker.ViewModel;
using System.Net.Http;
using VehicleTracker.Models;
using VehicleTracker.Helper;

namespace VehicleTracker.Controllers
{
    public class VehicleTypeController : Controller
    {
        public async Task<IActionResult> Index()
        {
            using (var client = new HttpClient())
            {
                try
                {
                    return View(await VehicleTypeVM.GetAllVehicleTypeAsync(client));
                }
                catch(Exception)
                {
                    return BadRequest("Get All Vehicle Type Fail");
                }
            }
        }

        [HttpGet]
        public IActionResult Insert()
        {
            return View();
        }

        [HttpPost]
        public async Task<IActionResult> Insert(VehicleType vehicleType)
        {
            using (var client = new HttpClient())
            {
                try
                {
                    String _result = await VehicleTypeVM.InsertVehicleTypeAsync(client, vehicleType);
                    if(_result.Equals(ResultCode.DONE))
                    {
                        return RedirectToAction("Index");
                    }
                    else
                    {
                        return BadRequest("Fail");
                    }
                }
                catch(Exception)
                {
                    return BadRequest("Connection Broken");
                }
            }
        }

        [HttpGet]
        public async Task<IActionResult> Edit(String Id)
        {
            using (var client = new HttpClient())
            {
                try
                {
                    return View(await VehicleTypeVM.GetVehicleTypeByIdAsync(client, Id));
                }
                catch(Exception)
                {
                    return BadRequest("Get Vehicle Type Fail");
                }
            }
        }

        [HttpPost]
        public async Task<IActionResult> Edit(VehicleType vehicleType)
        {
            using(var client = new HttpClient())
            {
                try
                {
                    String _result = await VehicleTypeVM.UpdateVehicleTypeAsync(client, vehicleType);
                    if (_result.Equals(ResultCode.DONE))
                    {
                        return RedirectToAction("Index", "VehicleType");
                    }
                    else
                    {
                        return BadRequest("Fail");
                    }
                }
                catch (Exception)
                {
                    return BadRequest("Connection Has Broken");
                }
            }
        }
    }
}