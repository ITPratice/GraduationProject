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
    public class BranchVM
    {
        public static async Task<IList<Branch>> GetAllBranchAsync(HttpClient client)
        {
            client.BaseAddress = new Uri(Constants.API_BASE_URL);
            var res = await client.GetAsync(Constants.API_GET_ALL_BRANCH);
            res.EnsureSuccessStatusCode();

            var strResult = await res.Content.ReadAsStringAsync();

            JObject _jObj = JObject.Parse(strResult);
            IList<JToken> results = _jObj["data"].Children().ToList();
            IList<Branch> _lstBranch = new List<Branch>();
            foreach (JToken result in results)
            {
                Branch _user = result.ToObject<Branch>();
                _lstBranch.Add(_user);
            }
            return _lstBranch;
        }

        public static async Task<Branch> GetBranchByIdAsync(HttpClient client, String Id)
        {
            client.BaseAddress = new Uri(Constants.API_BASE_URL);
            var res = await client.GetAsync($"api/branch?id={Id}");
            res.EnsureSuccessStatusCode();
            var strResult = await res.Content.ReadAsStringAsync();
            JObject _jObj = JObject.Parse(strResult);
            return _jObj.ToObject<Branch>();
        }

        public static async Task<String> UpdateBranchAsyn(HttpClient client, Branch branch)
        {
            client.BaseAddress = new Uri(Constants.API_BASE_URL);
            var res = await client.PutAsync($"api/branch?id={branch.Id}&name={branch.Name}", null);
            res.EnsureSuccessStatusCode();
            var strResult = await res.Content.ReadAsStringAsync();
            return strResult;
        }

        public static async Task<String> InsertBranchAsync(HttpClient client, Branch branch)
        {
            client.BaseAddress = new Uri(Constants.API_BASE_URL);
            var res = await client.PostAsync($"api/branch?id={branch.Id}&name={branch.Name}", null);
            res.EnsureSuccessStatusCode();
            var strResult = await res.Content.ReadAsStringAsync();
            return strResult;
        }
    }
}
