package self.yue.vehicletracker.util;

import android.Manifest;
import android.app.Activity;
import android.content.Context;
import android.content.pm.PackageManager;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;

/**
 * Created by dongc on 3/18/2017.
 */

public class PermissionChecker {
    public static final int PERMISSIONS_REQUEST_NETWORK_STATE = 430;
    public static final int PERMISSIONS_REQUEST_ACCESS_FINE_LOCATION = 384;

    public static boolean checkNetworkStatePermission(Activity activity) {
        if (!checkPermission(activity, Manifest.permission.ACCESS_NETWORK_STATE)) {
            ActivityCompat.requestPermissions(activity,
                    new String[]{Manifest.permission.ACCESS_NETWORK_STATE},
                    PERMISSIONS_REQUEST_NETWORK_STATE);
            return false;
        }
        return true;
    }

    public static boolean checkLocationPermission(Activity activity) {
        if (!checkPermission(activity, Manifest.permission.ACCESS_FINE_LOCATION)) {
            ActivityCompat.requestPermissions(activity,
                    new String[]{Manifest.permission.ACCESS_FINE_LOCATION},
                    PERMISSIONS_REQUEST_ACCESS_FINE_LOCATION);
            return false;
        }
        return true;
    }

    public static boolean checkPermission(Context context, String permission) {
        return ContextCompat.checkSelfPermission(context, permission) == PackageManager.PERMISSION_GRANTED;
    }
}
