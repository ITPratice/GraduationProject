using System;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Http;
using System.Net.Http;
using VehicleTracker.Helper;

namespace VehicleTracker.Controllers
{
    public class AdminController : Controller
    {
        public IActionResult Index()
        {
            return RedirectToAction("Index", "Vehicle");
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
                    client.BaseAddress = new Uri(Constants.API_BASE_URL);
                    var res = await client.GetAsync($"api/admin/login?email={_email}&pass={_pass}");
                    //res.EnsureSuccessStatusCode();
                    var strResult = await res.Content.ReadAsStringAsync();
                    if (strResult.Equals("\"SUCCESS\""))
                    {
                        return RedirectToAction("Index");
                    }
                    else
                    {
                        return RedirectToAction("Error", "Home");
                    }
                }
                catch (HttpRequestException ex)
                {
                    return (BadRequest($"Error getting: {ex.Message.ToString()}"));
                }
            }
        }
    }
}