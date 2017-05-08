using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Threading.Tasks;
using VehicleTracker.Helper;
using VehicleTracker.Models;

namespace VehicleTracker.ViewModel
{
    public class UserVM
    {
        public static async Task<IList<User>> GetAllUserAsync(HttpClient client)
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
            return lstUser;
        }

        public static async Task<IList<User>> GetAllUserActiveAsync(HttpClient client)
        {
            client.BaseAddress = new Uri(Constants.API_BASE_URL);
            var res = await client.GetAsync(Constants.API_GET_ALL_USER_ACTIVE);
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
            return lstUser;
        }

        public static async Task<User> GetUserByEmailAsync(HttpClient client, String email)
        {
            client.BaseAddress = new Uri(Constants.API_BASE_URL);
            var res = await client.GetAsync($"api/user?email={email}");
            res.EnsureSuccessStatusCode();
            var strResult = await res.Content.ReadAsStringAsync();
            JObject _jObj = JObject.Parse(strResult);
            return _jObj.ToObject<User>();
        }

        public static async Task<String> UpdateUserAsync(HttpClient client, User user)
        {
            client.BaseAddress = new Uri(Constants.API_BASE_URL);
            var res = await client.PutAsync($"api/user?email={user.Email}&username={user.UserName}&address={user.Address}&phone={user.PhoneNumber}&pass={user.PassWord}&name={user.FullName}&role={user.Role}&first={user.First}", null);
            res.EnsureSuccessStatusCode();
            var strResult = await res.Content.ReadAsStringAsync();
            return strResult;
        }

        public static async Task<String> RegistrationAsync(HttpClient client, User user)
        {
            client.BaseAddress = new Uri(Constants.API_BASE_URL);
            var res = await client.PostAsync($"api/user?email={user.Email}&username={user.UserName}&address={user.Address}&phone={user.PhoneNumber}&pass={user.PassWord}&name={user.FullName}&role={user.Role}&first={user.First}", null);
            res.EnsureSuccessStatusCode();
            var strResult = await res.Content.ReadAsStringAsync();
            return strResult;
        }

        public static async Task<String> ActiveUserAsync(HttpClient client, String email)
        {
            client.BaseAddress = new Uri(Constants.API_BASE_URL);
            var res = await client.PutAsync($"api/user/active?email={email}", null);
            res.EnsureSuccessStatusCode();
            var strResult = await res.Content.ReadAsStringAsync();
            return strResult;
        }
    }
}
