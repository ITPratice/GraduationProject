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
    public static final int REQUEST_CODE_NETWORK_STATE_PERMISSION = 430;

    public static void requestNetworkStatePermission(Activity activity) {
        ActivityCompat.requestPermissions(activity,
                new String[]{Manifest.permission.ACCESS_NETWORK_STATE},
                REQUEST_CODE_NETWORK_STATE_PERMISSION);
    }

    public static boolean checkPermission(Context context, String permission) {
        return ContextCompat.checkSelfPermission(context, permission) == PackageManager.PERMISSION_GRANTED;
    }
}
