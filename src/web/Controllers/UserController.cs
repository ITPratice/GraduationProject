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
    enum ResultCode
    {
        DONE = 1,
        URL_INVALID,
        ERROR,
        UNKNOWN,
        NOT_SUPPORT
    }

    public class UserController : Controller
    {
        public async Task<IActionResult> Index()
        {
            return View(await UserVM.GetAllUser());
        }

        [HttpGet]
        public async Task<IActionResult> Edit(string email)
        {
            return View(await UserVM.GetUserByEmail(email));
        }

        [HttpPost]
        public async Task<IActionResult> Edit([Bind("Address", "Email", "FullName", "PassWord", "PhoneNumber", "UserName", "Role")] User user)
        {
            String strResult = await UserVM.UpdateUser(user);
            if (strResult.Equals("\"OK\""))
            {
                return RedirectToAction("Index");
            }
            else
            {
                return (BadRequest("Fail"));
            }
        }

        public async Task<IActionResult> Active()
        {
            return View(await UserVM.GetAllUserActive());
        }

        public async Task<IActionResult> Test(String email)
        {
            String _result = await UserVM.ActiveUserAsync(email);
            if(_result.Equals("1"))
            {
                return RedirectToAction("Active", "User");
            }
            else
            {
                return (BadRequest("Fail"));
            }
        }
    }
}