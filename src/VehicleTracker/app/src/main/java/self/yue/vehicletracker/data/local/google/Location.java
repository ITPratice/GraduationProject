package self.yue.vehicletracker.data.local.google;

import com.google.android.gms.maps.model.LatLng;

/**
 * Created by dongc on 4/20/2017.
 */

public class Location {
    public float lat;
    public float lng;

    public LatLng toLatLng() {
        return new LatLng(lat, lng);
    }
}
