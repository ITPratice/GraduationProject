package self.yue.vehicletracker.data.local.google;

import com.google.gson.annotations.SerializedName;

import java.util.List;

/**
 * Created by dongc on 4/20/2017.
 */

public class Leg {
    public Distance distance;
    @SerializedName("start_location")
    public Location startLocation;
    @SerializedName("end_location")
    public Location endLocation;
    public List<Step> steps;
}
