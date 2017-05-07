using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using System.Net.Http;
using VehicleTracker.Models;
using VehicleTracker.ViewModel;
using VehicleTracker.Helper;

namespace VehicleTracker.Controllers
{
    public class BranchController : Controller
    {
        public async Task<IActionResult> Index()
        {
            using (var client = new HttpClient())
            {
                try
                {
                    return View(await BranchVM.GetAllBranchAsync(client));
                }
                catch(Exception)
                {
                    return BadRequest("Connection has broken");
                }
            }
        }

        [HttpGet]
        public IActionResult Insert()
        {
            return View();
        }

        [HttpPost]
        public async Task<IActionResult> Insert(Branch branch)
        {
            using (var client = new HttpClient())
            {
                try
                {
                    String _result = await BranchVM.InsertBranchAsync(client, branch);
                    return _result.Equals(ResultCode.DONE) ? RedirectToAction("Index", "Branch") : RedirectToAction("Home", "Error");
                }
                catch
                {
                    return BadRequest("Connection Has Broken");
                }
            }
        }

        [HttpGet]
        public async Task<IActionResult> Edit(String Id)
        {
            using (var client = new HttpClient())
            {
                try
                {
                    return View(await BranchVM.GetBranchByIdAsync(client, Id));
                }
                catch(Exception)
                {
                    return BadRequest("Connection Has Broken");
                }
            }
        }

        [HttpPost]
        public async Task<IActionResult> Edit(Branch branch)
        {
            using (var client = new HttpClient())
            {
                try
                {
                    String _result = await BranchVM.UpdateBranchAsyn(client, branch);
                    if (_result.Equals(ResultCode.DONE))
                    {
                        return RedirectToAction("Index", "Branch");
                    }
                    else
                    {
                        return BadRequest("Fail");
                    }
                }
                catch(Exception)
                {
                    return BadRequest("Connection Has Broken");
                }
            }
        }
    }
}