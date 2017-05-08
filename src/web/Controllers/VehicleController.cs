using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using System.Net.Http;
using VehicleTracker.ViewModel;
using VehicleTracker.Helper;
using VehicleTracker.Models;

namespace VehicleTracker.Controllers
{
    public class VehicleController : Controller
    {
        public async Task<IActionResult> Index()
        {
            using (var client = new HttpClient())
            {
                try
                {
                    return View(await VehicleVM.GetAllVehicleAsync(client));
                }
                catch(Exception)
                {
                    return BadRequest(Lang.LANG_CONNECTION_PROBLEM);
                }
            }
        }

        [HttpGet]
        public async Task<IActionResult> Edit(String numberPlate)
        {
            using (var client = new HttpClient())
            {
                try
                {
                    return View(await VehicleVM.GetVehicleByNumberPlateAsync(client, numberPlate));
                }
                catch(Exception)
                {
                    return BadRequest(Lang.LANG_CONNECTION_PROBLEM);
                }
            }
        }

        [HttpPost]
        public async Task<IActionResult> Edit(Vehicle vehicle)
        {
            using (var client = new HttpClient())
            {
                try
                {
                    String _result = await VehicleVM.UpdateVehicleAsync(client, vehicle);
                    if (_result.Equals(ResultCode.DONE))
                    {
                        return RedirectToAction("Index");
                    }
                    else
                    {
                        return BadRequest(Lang.LANG_UPDATE_PROBLEM);
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