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
            if (HttpContext.Session.GetString("Admin") == String.Empty)
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
            String _email = form["Email"].ToString();
            String _pass = form["PassWord"].ToString();

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
                        return Content("<script>alert('Error');</script>");
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