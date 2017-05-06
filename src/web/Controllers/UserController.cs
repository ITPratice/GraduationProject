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
    }
}