package self.yue.vehicletracker.services;

import android.app.Service;
import android.content.Intent;
import android.os.CountDownTimer;
import android.os.IBinder;
import android.support.annotation.Nullable;
import android.text.TextUtils;

import self.yue.vehicletracker.data.local.Location;
import self.yue.vehicletracker.data.server.ApiProvider;
import self.yue.vehicletracker.util.CommonConstants;
import self.yue.vehicletracker.util.interfaces.OnServerResponseListener;

/**
 * Created by dongc on 5/6/2017.
 */

public class VehicleLocationUpdateService extends Service {
    private static final int UPDATE_INTERVAL = 10000;

    private CountDownTimer mTimer;

    private String mLicensePlate;
    private Location mCurrentLocation;

    private boolean mIsTimerRunning;

    @Override
    public void onCreate() {
        super.onCreate();

        mIsTimerRunning = false;

        mTimer = new CountDownTimer(Long.MAX_VALUE, UPDATE_INTERVAL) {
            @Override
            public void onTick(long millisUntilFinished) {
                updateVehicleLocation();
            }

            @Override
            public void onFinish() {

            }
        };
    }

    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        if (intent != null) {
            switch (intent.getAction()) {
                case CommonConstants.ACTION_UPDATE_VEHICLE_LOCATION:
                    updateVehicleLocation();
                    if (!mIsTimerRunning) {
                        mTimer.start();
                        mIsTimerRunning = true;
                    }
                    break;
                case CommonConstants.ACTION_UPDATE_LICENSE_PLATE:
                    mLicensePlate = intent.getStringExtra(CommonConstants.EXTRA_LICENSE_PLATE);
                    updateVehicleLocation();
                    if (!mIsTimerRunning) {
                        mTimer.start();
                        mIsTimerRunning = true;
                    }
                    break;
                case CommonConstants.ACTION_GET_CURRENT_VEHICLE_LOCATION:
                    if (mCurrentLocation != null) {
                        Intent broadcastIntent = new Intent(CommonConstants.ACTION_RECEIVE_VEHICLE_LOCATION);
                        broadcastIntent.putExtra(CommonConstants.EXTRA_LATITUDE, mCurrentLocation.latitude);
                        broadcastIntent.putExtra(CommonConstants.EXTRA_LONGITUDE, mCurrentLocation.longitude);
                        sendBroadcast(broadcastIntent);
                    }
                    break;
            }
        }
        return super.onStartCommand(intent, flags, startId);
    }

    private void updateVehicleLocation() {
        if (!TextUtils.isEmpty(mLicensePlate)) {
            ApiProvider.getInstance().getCurrentLocation(mLicensePlate,
                    new OnServerResponseListener<Location>() {
                        @Override
                        public void onSuccess(Location data) {
                            mCurrentLocation = data;

                            Intent intent = new Intent(CommonConstants.ACTION_RECEIVE_VEHICLE_LOCATION);
                            intent.putExtra(CommonConstants.EXTRA_LATITUDE, data.latitude);
                            intent.putExtra(CommonConstants.EXTRA_LONGITUDE, data.longitude);
                            sendBroadcast(intent);
                        }

                        @Override
                        public void onFail(Throwable t) {

                        }
                    });
        }
    }
}