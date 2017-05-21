using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using System.Net.Http;
using VehicleTracker.ViewModel;
using VehicleTracker.Helper;
using VehicleTracker.Models;
using Microsoft.AspNetCore.Http;

namespace VehicleTracker.Controllers
{
    public class VehicleController : Controller
    {
        public async Task<IActionResult> Index()
        {
            if (HttpContext.Session.GetString("Admin") == null)
            {
                return RedirectToAction("Login", "Admin");
            }

            using (var client = new HttpClient())
            {
                try
                {
                    return View(await VehicleVM.GetAllVehicleAsync(client));
                }
                catch (Exception)
                {
                    return BadRequest(Lang.LANG_CONNECTION_PROBLEM);
                }
            }
        }

        [HttpGet]
        public async Task<IActionResult> Edit(String numberPlate)
        {
            if (HttpContext.Session.GetString("Admin") == null)
            {
                return RedirectToAction("Login", "Admin");
            }

            using (var client = new HttpClient())
            {
                try
                {
                    return View(await VehicleVM.GetVehicleByNumberPlateAsync(client, numberPlate));
                }
                catch (Exception)
                {
                    return BadRequest(Lang.LANG_CONNECTION_PROBLEM);
                }
            }
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(Vehicle vehicle)
        {
            if (ModelState.IsValid)
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
                    catch (Exception)
                    {
                        return BadRequest(Lang.LANG_CONNECTION_PROBLEM);
                    }
                }
            }
            return View();
        }

        public async Task<IActionResult> Delete(string numberPlate)
        {
            using (var client = new HttpClient())
            {
                try
                {
                    String _result = await VehicleVM.DeleteVehicleAsync(client, numberPlate);
                    if (_result.Equals(ResultCode.DONE))
                    {
                        return RedirectToAction("Index");
                    }
                    else
                    {
                        return BadRequest(Lang.LANG_UPDATE_PROBLEM);
                    }
                }
                catch (Exception)
                {
                    return BadRequest(Lang.LANG_CONNECTION_PROBLEM);
                }
            }
        }
    }
}