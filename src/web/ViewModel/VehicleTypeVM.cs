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
    public class VehicleTypeVM
    {
        public static async Task<IList<VehicleType>> GetAllVehicleTypeAsync(HttpClient client)
        {
            client.BaseAddress = new Uri(Constants.API_BASE_URL);
            var res = await client.GetAsync(Constants.API_GET_ALL_VEHICLE_TYPE);
            res.EnsureSuccessStatusCode();

            var strResult = await res.Content.ReadAsStringAsync();

            JObject _jObj = JObject.Parse(strResult);
            IList<JToken> results = _jObj["data"].Children().ToList();
            IList<VehicleType> _lstVehicleType = new List<VehicleType>();
            foreach (JToken result in results)
            {
                VehicleType _vehicleType = result.ToObject<VehicleType>();
                _lstVehicleType.Add(_vehicleType);
            }
            return _lstVehicleType;
        }

        public static async Task<VehicleType> GetVehicleTypeByIdAsync(HttpClient client, String Id)
        {
            client.BaseAddress = new Uri(Constants.API_BASE_URL);
            var res = await client.GetAsync($"api/vehicletype?id={Id}");
            res.EnsureSuccessStatusCode();
            var strResult = await res.Content.ReadAsStringAsync();
            JObject _jObj = JObject.Parse(strResult);
            return _jObj.ToObject<VehicleType>();
        }

        public static async Task<String> UpdateVehicleTypeAsync(HttpClient client, VehicleType vehicleType)
        {
            client.BaseAddress = new Uri(Constants.API_BASE_URL);
            var res = await client.PutAsync($"api/vehicletype?id={vehicleType.Id}&name={vehicleType.Name}", null);
            res.EnsureSuccessStatusCode();
            var strResult = await res.Content.ReadAsStringAsync();
            return strResult;
        }

        public static async Task<String> InsertVehicleTypeAsync(HttpClient client, VehicleType vehicleType)
        {
            client.BaseAddress = new Uri(Constants.API_BASE_URL);
            var res = await client.PostAsync($"api/vehicletype?id={vehicleType.Id}&name={vehicleType.Name}", null);
            res.EnsureSuccessStatusCode();
            var strResult = await res.Content.ReadAsStringAsync();
            return strResult;
        }
    }
}
