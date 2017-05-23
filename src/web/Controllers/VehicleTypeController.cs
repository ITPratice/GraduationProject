using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using VehicleTracker.ViewModel;
using System.Net.Http;
using VehicleTracker.Models;
using VehicleTracker.Helper;
using Microsoft.AspNetCore.Http;

namespace VehicleTracker.Controllers
{
    public class VehicleTypeController : Controller
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
                    return View(await VehicleTypeVM.GetAllVehicleTypeAsync(client));
                }
                catch (Exception)
                {
                    return BadRequest(Lang.LANG_SELECT_PROBLEM);
                }
            }
        }

        [HttpGet]
        public IActionResult Insert()
        {
            if (HttpContext.Session.GetString("Admin") == null)
            {
                return RedirectToAction("Login", "Admin");
            }
            return View();
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Insert(VehicleType vehicleType)
        {
            if (ModelState.IsValid)
            {
                using (var client = new HttpClient())
                {
                    try
                    {
                        String _result = await VehicleTypeVM.InsertVehicleTypeAsync(client, vehicleType);
                        if (_result.Equals(ResultCode.DONE))
                        {
                            return RedirectToAction("Index");
                        }
                        else
                        {
                            return BadRequest(Lang.LANG_INSERT_PROBLEM);
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
        public async Task<IActionResult> Edit(String Id)
        {
            if (HttpContext.Session.GetString("Admin") == null)
            {
                return RedirectToAction("Login", "Admin");
            }

            using (var client = new HttpClient())
            {
                try
                {
                    return View(await VehicleTypeVM.GetVehicleTypeByIdAsync(client, Id));
                }
                catch (Exception)
                {
                    return BadRequest(Lang.LANG_SELECT_PROBLEM);
                }
            }
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(VehicleType vehicleType)
        {
            if (ModelState.IsValid)
            {
                using (var client = new HttpClient())
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

        public async Task<IActionResult> Delete(String Id, String Name)
        {
            using (HttpClient client = new HttpClient())
            {
                try
                {
                    String _result = await VehicleTypeVM.DeleteVehicleTypeAsync(client, Id, Name);
                    if (_result.Equals(ResultCode.DONE))
                    {
                        return RedirectToAction("Index");
                    }
                    else
                    {
                        return BadRequest(Lang.LANG_DELETE_PROBLEM);
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