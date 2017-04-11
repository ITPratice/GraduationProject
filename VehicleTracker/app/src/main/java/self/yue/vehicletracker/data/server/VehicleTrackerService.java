package self.yue.vehicletracker.data.server;

import java.util.List;

import retrofit2.Call;
import retrofit2.http.GET;
import self.yue.vehicletracker.data.local.ServerResponse;
import self.yue.vehicletracker.data.local.User;

/**
 * Created by dongc on 4/11/2017.
 */

public interface VehicleTrackerService {
    @GET("user/all")
    Call<ServerResponse<List<User>>> getAllUsers();
}
