using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using System.Net.Http;
using VehicleTracker.Helper;
using Newtonsoft.Json.Linq;
using VehicleTracker.Models;
using VehicleTracker.ViewModel;

namespace VehicleTracker.Controllers
{
    public class UserController : Controller
    {
        public async Task<IActionResult> Index()
        {
            using (var client = new HttpClient())
            {
                try
                {
                    return View(await UserVM.GetAllUserAsync(client));
                }
                catch(Exception)
                {
                    return BadRequest(Lang.LANG_CONNECTION_PROBLEM);
                }
            }
        }

        [HttpGet]
        public async Task<IActionResult> Edit(string email)
        {
            using (var client = new HttpClient())
            {
                try
                {
                    return View(await UserVM.GetUserByEmailAsync(client, email));
                }
                catch(Exception)
                {
                    return BadRequest(Lang.LANG_CONNECTION_PROBLEM);
                }
            }
        }

        [HttpPost]
        public async Task<IActionResult> Edit(User user)
        {
            using (var client = new HttpClient())
            {
                try
                {
                    String strResult = await UserVM.UpdateUserAsync(client, user);
                    if (strResult.Equals(ResultCode.DONE))
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

        public async Task<IActionResult> Active()
        {
            using (var client = new HttpClient())
            {
                try
                {
                    return View(await UserVM.GetAllUserActiveAsync(client));
                }
                catch(Exception)
                {
                    return BadRequest(Lang.LANG_CONNECTION_PROBLEM);
                }
            }
        }

        public async Task<IActionResult> Test(String email)
        {
            using (var client = new HttpClient())
            {
                try
                {
                    String _result = await UserVM.ActiveUserAsync(client, email);
                    if (_result.Equals(ResultCode.DONE))
                    {
                        return RedirectToAction("Active", "User");
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