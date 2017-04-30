package self.yue.vehicletracker.data.server;

import okhttp3.ResponseBody;
import retrofit2.Call;
import retrofit2.http.GET;
import retrofit2.http.Query;
import self.yue.vehicletracker.data.local.google.GoogleServerResponse;
import self.yue.vehicletracker.data.local.google.Route;

/**
 * Created by dongc on 4/20/2017.
 */

public interface GoogleService {
    @GET("directions/json")
    Call<GoogleServerResponse> getDirection(@Query("origin") String origin,
                                            @Query("destination") String destination,
                                            @Query("key") String key);
}
