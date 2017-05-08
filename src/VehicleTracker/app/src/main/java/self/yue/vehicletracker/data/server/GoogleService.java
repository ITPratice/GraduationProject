package self.yue.vehicletracker.data.server;

import retrofit2.Call;
import retrofit2.http.GET;
import retrofit2.http.Query;
import self.yue.vehicletracker.data.local.google.GoogleServerResponse;

/**
 * Created by dongc on 4/20/2017.
 */

public interface GoogleService {
    @GET("directions/json")
    Call<GoogleServerResponse> getDirection(@Query("origin") String origin,
                                            @Query("destination") String destination,
                                            @Query("key") String key);
}
