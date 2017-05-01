package self.yue.vehicletracker.util;

import android.Manifest;
import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;

/**
 * Created by dongc on 3/18/2017.
 */

public class CommonUtil {

    // Check if device is connect to the internet or not
    public static boolean isNetworkAvailable(Context context) {
        if (PermissionChecker.checkPermission(context, Manifest.permission.ACCESS_NETWORK_STATE)) {
            ConnectivityManager cm =
                    (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);
            NetworkInfo activeNetwork = cm.getActiveNetworkInfo();
            return activeNetwork != null && activeNetwork.isConnectedOrConnecting();
        }
        return false;
    }
}
