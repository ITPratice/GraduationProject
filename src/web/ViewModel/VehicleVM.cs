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
    public class VehicleVM
    {
        public static async Task<IList<Vehicle>> GetAllVehicleAsync(HttpClient client)
        {
            client.BaseAddress = new Uri(Constants.API_BASE_URL);
            var res = await client.GetAsync(Constants.API_GET_ALL_VEHICLE);
            res.EnsureSuccessStatusCode();

            var strResult = await res.Content.ReadAsStringAsync();

            JObject _jObj = JObject.Parse(strResult);
            IList<JToken> results = _jObj["data"].Children().ToList();
            IList<Vehicle> _lstVehicle = new List<Vehicle>();
            foreach (JToken result in results)
            {
                Vehicle _vehicle = result.ToObject<Vehicle>();
                _lstVehicle.Add(_vehicle);
            }
            return _lstVehicle;
        }

        public static async Task<Vehicle> GetVehicleByNumberPlateAsync(HttpClient client, String numberPlate)
        {
            client.BaseAddress = new Uri(Constants.API_BASE_URL);
            var res = await client.GetAsync($"api/vehicle?plate={numberPlate}");
            res.EnsureSuccessStatusCode();
            var strResult = await res.Content.ReadAsStringAsync();
            JObject _jObj = JObject.Parse(strResult);
            return _jObj.ToObject<Vehicle>();
        }

        public static async Task<String> UpdateVehicleAsync(HttpClient client, Vehicle vehicle)
        {
            client.BaseAddress = new Uri(Constants.API_BASE_URL);
            var res = await client.PutAsync($"api/vehicle?plate={vehicle.NumberPlate}&brand={vehicle.BranchId}&hardware={vehicle.HardwareId}&description={vehicle.Description}&type={vehicle.TypeId}&email={vehicle.UserEmail}&deleted={vehicle.Deleted}&write={vehicle.WriteHistory}", null);
            res.EnsureSuccessStatusCode();
            var strResult = await res.Content.ReadAsStringAsync();
            return strResult;
        }

        public static async Task<String> InsertVehicleAsync(HttpClient client, Vehicle vehicle)
        {
            client.BaseAddress = new Uri(Constants.API_BASE_URL);
            var res = await client.PostAsync($"api/vehicle?plate={vehicle.NumberPlate}&brand={vehicle.BranchId}&hardware={vehicle.HardwareId}&description={vehicle.Description}&type={vehicle.TypeId}&email={vehicle.UserEmail}&deleted={vehicle.Deleted}&write={vehicle.WriteHistory}", null);
            res.EnsureSuccessStatusCode();
            var strResult = await res.Content.ReadAsStringAsync();
            return strResult;
        }
    }
}
