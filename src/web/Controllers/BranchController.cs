using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using System.Net.Http;
using VehicleTracker.Models;
using VehicleTracker.ViewModel;
using VehicleTracker.Helper;
using Microsoft.AspNetCore.Http;

namespace VehicleTracker.Controllers
{
    public class BranchController : Controller
    {
        public async Task<IActionResult> Index()
        {
            if (HttpContext.Session.GetString("Admin") == null)
            {
                return RedirectToAction("Login", "Admin");
            }

            using (var client = new HttpClient())
            {
                try
                {
                    return View(await BranchVM.GetAllBranchAsync(client));
                }
                catch (Exception)
                {
                    return BadRequest(Lang.LANG_CONNECTION_PROBLEM);
                }
            }
        }

        [HttpGet]
        public IActionResult Insert()
        {
            if (HttpContext.Session.GetString("Admin") == null)
            {
                return RedirectToAction("Login", "Admin");
            }
            return View();
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Insert(Branch branch)
        {
            if (ModelState.IsValid)
            {
                using (var client = new HttpClient())
                {
                    try
                    {
                        String _result = await BranchVM.InsertBranchAsync(client, branch);
                        if (_result.Equals(ResultCode.DONE))
                        {
                            return RedirectToAction("Index", "Branch");
                        }
                        else
                        {
                            ModelState.AddModelError("", Lang.LANG_INSERT_PROBLEM);
                        }
                    }
                    catch
                    {
                        return BadRequest(Lang.LANG_CONNECTION_PROBLEM);
                    }
                }
            }
            return View();
        }

        [HttpGet]
        public async Task<IActionResult> Edit(String Id)
        {
            if (HttpContext.Session.GetString("Admin") == null)
            {
                return RedirectToAction("Login", "Admin");
            }

            using (var client = new HttpClient())
            {
                try
                {
                    return View(await BranchVM.GetBranchByIdAsync(client, Id));
                }
                catch (Exception)
                {
                    return BadRequest(Lang.LANG_CONNECTION_PROBLEM);
                }
            }
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(Branch branch)
        {
            if (ModelState.IsValid)
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
                            ModelState.AddModelError("", Lang.LANG_UPDATE_PROBLEM);
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

        public async Task<IActionResult> Delete(String Id, String Name)
        {
            using (HttpClient client = new HttpClient())
            {
                try
                {
                    String _result = await BranchVM.DeleteBranchAsync(client, Id, Name);
                    if (_result.Equals(ResultCode.DONE))
                    {
                        return RedirectToAction("Index");
                    }
                    else
                    {
                        return BadRequest(Lang.LANG_DELETE_PROBLEM);
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