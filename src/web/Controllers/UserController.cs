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
using Microsoft.AspNetCore.Http;

namespace VehicleTracker.Controllers
{
    public class UserController : Controller
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
                    return View(await UserVM.GetAllUserAsync(client));
                }
                catch (Exception)
                {
                    return BadRequest(Lang.LANG_CONNECTION_PROBLEM);
                }
            }
        }

        [HttpGet]
        public async Task<IActionResult> Edit(string email)
        {
            if (HttpContext.Session.GetString("Admin") == null)
            {
                return RedirectToAction("Login", "Admin");
            }

            using (var client = new HttpClient())
            {
                try
                {
                    if (email.Equals(String.Empty))
                    {
                        return BadRequest(Lang.LANG_EMAIL_NOT_FOUND);
                    }
                    return View(await UserVM.GetUserByEmailAsync(client, email));
                }
                catch (Exception)
                {
                    return BadRequest(Lang.LANG_CONNECTION_PROBLEM);
                }
            }
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(User user)
        {
            if (ModelState.IsValid)
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
                    catch (Exception)
                    {
                        return BadRequest(Lang.LANG_CONNECTION_PROBLEM);
                    }
                }
            }
            return View();
        }

        public async Task<IActionResult> Active()
        {
            if (HttpContext.Session.GetString("Admin") == null)
            {
                return RedirectToAction("Login", "Admin");
            }

            using (var client = new HttpClient())
            {
                try
                {
                    return View(await UserVM.GetAllUserActiveAsync(client));
                }
                catch (Exception)
                {
                    return BadRequest(Lang.LANG_CONNECTION_PROBLEM);
                }
            }
        }

        public async Task<IActionResult> Delete(string email)
        {
            using (var client = new HttpClient())
            {
                try
                {
                    if (email.Equals(String.Empty))
                    {
                        return BadRequest(Lang.LANG_EMAIL_NOT_FOUND);
                    }
                    String result = await UserVM.DeleteUserAsync(client, email);
                    if (result.Equals(ResultCode.DONE))
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


        // Just Test
        public async Task<IActionResult> Actived(String email)
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
                catch (Exception)
                {
                    return BadRequest(Lang.LANG_CONNECTION_PROBLEM);
                }
            }

        }
    }
}