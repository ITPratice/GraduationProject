using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using System.Net.Http;
using VehicleTracker.Helper;
using Newtonsoft.Json.Linq;
using VehicleTracker.Models;

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
                    client.BaseAddress = new Uri(Constants.API_BASE_URL);
                    var res = await client.GetAsync(Constants.API_GET_ALL_USER);
                    res.EnsureSuccessStatusCode();

                    var strResult = await res.Content.ReadAsStringAsync();

                    JObject _jObj = JObject.Parse(strResult);
                    IList<JToken> results = _jObj["data"].Children().ToList();
                    IList<User> lstUser = new List<User>();
                    foreach (JToken result in results)
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

        [HttpGet]
        public async Task<IActionResult> Edit(string email)
        {
            using (var client = new HttpClient())
            {
                try
                {
                    client.BaseAddress = new Uri(Constants.API_BASE_URL);
                    var res = await client.GetAsync($"api/user?email={email}");
                    res.EnsureSuccessStatusCode();
                    var strResult = await res.Content.ReadAsStringAsync();
                    JObject _jObj = JObject.Parse(strResult);
                    User _user = _jObj.ToObject<User>();
                    return View(_user);
                }
                catch (HttpRequestException ex)
                {
                    return (BadRequest($"Error getting: {ex.Message.ToString()}"));
                }
            }
        }

        [HttpPost]
        public async Task<IActionResult> Edit([Bind("Address", "Email", "FullName", "PassWord", "PhoneNumber", "UserName", "Role")] User user)
        {
            using (var client = new HttpClient())
            {
                try
                {
                    client.BaseAddress = new Uri(Constants.API_BASE_URL);
                    var res = await client.PutAsync($"api/user?email={user.Email}&username={user.UserName}&address={user.Address}&phone={user.PhoneNumber}&pass={user.PassWord}&name={user.FullName}&role={user.Role}", null);
                    res.EnsureSuccessStatusCode();
                    var strResult = await res.Content.ReadAsStringAsync();
                    if(strResult.Equals("\"OK\""))
                    {
                        return RedirectToAction("Index");
                    }
                    else
                    {
                        return (BadRequest("Fail"));
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