package self.yue.vehicletracker.data.local.google;

import com.google.gson.annotations.SerializedName;

/**
 * Created by dongc on 4/20/2017.
 */

public class Step {
    public Distance distance;
    public Polyline polyline;
    @SerializedName("start_location")
    public Location startLocation;
    @SerializedName("end_location")
    public Location endLocation;
}
