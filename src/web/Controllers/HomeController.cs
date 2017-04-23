using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using System.Net;
using System.IO;
using System.Net.Http;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using VehicleTracker.Models;
using VehicleTracker.Helper;

namespace VehicleTracker.Controllers
{
    public class HomeController : Controller
    {
        public IActionResult Index()
        {
            return View();
        }

        public async Task<IActionResult> Test()
        {
            using(var client = new HttpClient())
            {
                try
                {
                    client.BaseAddress = new Uri(Constants.API_BASE_URL);
                    var res = await client.GetAsync($"api/user/all");
                    res.EnsureSuccessStatusCode();

                    var strResult = await res.Content.ReadAsStringAsync();

                    JObject _jObj = JObject.Parse(strResult);
                    IList<JToken> results = _jObj["data"].Children().ToList();
                    IList<User> lstUser = new List<User>();
                    foreach(JToken result in results)
                    {
                        User _user = result.ToObject<User>();
                        lstUser.Add(_user);
                    }
                    return View(lstUser);
                }
                catch (HttpRequestException ex)
                {
                    return (BadRequest($"Error getting: {ex.Message.ToString()}"));
                }
            }
        }
    }
}