package self.yue.vehicletracker.data.server;

import java.util.List;

import okhttp3.ResponseBody;
import retrofit2.Call;
import retrofit2.http.GET;
import retrofit2.http.PUT;
import retrofit2.http.Query;
import self.yue.vehicletracker.data.local.Location;
import self.yue.vehicletracker.data.local.ServerHistory;
import self.yue.vehicletracker.data.local.ServerResponse;
import self.yue.vehicletracker.data.local.User;
import self.yue.vehicletracker.data.local.Vehicle;

/**
 * Created by dongc on 4/11/2017.
 */

public interface VehicleTrackerService {
    @GET("user/all")
    Call<ServerResponse<List<User>>> getAllUsers();

    @GET("user/login")
    Call<ResponseBody> login(@Query("email") String email, @Query("pass") String password);

    @PUT("user")
    Call<String> updateProfile(@Query("email") String email,
                               @Query("username") String username,
                               @Query("address") String address,
                               @Query("phone") String phone,
                               @Query("pass") String pass,
                               @Query("name") String name,
                               @Query("role") int role,
                               @Query("first") int isFirst);

    @GET("user")
    Call<User> getUserByEmail(@Query("email") String email);

    @GET("location/current")
    Call<Location> getCurrentLocation(@Query("plate") String licensePlate);

    @GET("vehicle/user")
    Call<ServerResponse<List<Vehicle>>> getUserVehicles(@Query("email") String email);

    @GET("location")
    Call<ServerResponse<List<ServerHistory>>> getLocationByDate(@Query("plate") String licensePlate,
                                                                @Query("date") String date);

    @GET("user/first")
    Call<String> changePasswordForFirstTime(@Query("email") String email,
                                            @Query("pass") String password);

    @PUT("vehicle")
    Call<ResponseBody> updateVehicleState(@Query("plate") String licensePlate,
                                          @Query("brand") String brandId,
                                          @Query("hardware") String hardwareId,
                                          @Query("description") String description,
                                          @Query("type") String type,
                                          @Query("email") String email,
                                          @Query("deleted") String isDeleted,
                                          @Query("write") String writable);

    @GET("vehicle")
    Call<Vehicle> getVehicle(@Query("plate") String licensePlate);
}
