package self.yue.vehicletracker;

import android.app.Application;

import self.yue.vehicletracker.data.server.ApiProvider;
import self.yue.vehicletracker.util.CacheHelper;
import self.yue.vehicletracker.util.FontUtil;

/**
 * Created by dongc on 5/3/2017.
 */

public class VehicleTrackerApplication extends Application {

    @Override
    public void onCreate() {
        super.onCreate();
        FontUtil.getInstance().init(this);
        ApiProvider.getInstance().init(this);
        CacheHelper.getInstance().init(this);
    }
}
