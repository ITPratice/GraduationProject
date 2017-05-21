using System;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Http;
using System.Net.Http;
using VehicleTracker.Helper;
using VehicleTracker.ViewModel;

namespace VehicleTracker.Controllers
{
    public class AdminController : Controller
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

        [HttpGet]
        public IActionResult Login()
        {
            return View();
        }

        [HttpPost]
        public async Task<IActionResult> Login(IFormCollection form)
        {
            //if (HttpContext.Session.GetString("Admin") != String.Empty)
            //{
            //    return RedirectToAction("Index", "Vehicle");
            //}
            String _email = form["Email"].ToString();
            String _pass = form["PassWord"].ToString();
            if (ModelState.IsValid)
            {
                using (var client = new HttpClient())
                {
                    try
                    {
                        var result = await UserVM.LoginAdminAsync(client, _email, _pass);
                        if (result.Equals(ResultCode.DONE))
                        {
                            HttpContext.Session.SetString("Admin", _email);
                            return RedirectToAction("Index");
                        }
                        else
                        {
                            ModelState.AddModelError("", Lang.LANG_LOGIN_FAIL);
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

        public IActionResult Logout()
        {
            if (HttpContext.Session.GetString("Admin") != null || HttpContext.Session.GetString("Admin") != String.Empty)
            {
                HttpContext.Session.SetString("Admin", String.Empty);
            }
            return RedirectToAction("Login", "Admin");
        }
    }
}