package self.yue.vehicletracker.ui.main.home;

import android.app.ProgressDialog;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.IntentSender;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.view.View;
import android.widget.Toast;

import com.google.android.gms.common.api.ResultCallback;
import com.google.android.gms.common.api.Status;
import com.google.android.gms.location.LocationSettingsResult;
import com.google.android.gms.location.LocationSettingsStatusCodes;
import com.google.android.gms.maps.model.LatLng;

import self.yue.vehicletracker.R;
import self.yue.vehicletracker.base.BasePage;
import self.yue.vehicletracker.data.local.google.Route;
import self.yue.vehicletracker.data.server.GoogleApiProvider;
import self.yue.vehicletracker.services.VehicleLocationUpdateService;
import self.yue.vehicletracker.ui.map.MapFragment;
import self.yue.vehicletracker.util.CommonConstants;
import self.yue.vehicletracker.util.interfaces.OnServerResponseListener;

import static self.yue.vehicletracker.ui.map.MapFragment.REQUEST_CODE_GPS;

/**
 * Created by dongc on 3/25/2017.
 */

public class HomeFragment extends BasePage {
    private MapFragment mMapFragment;
    private LatLng mCurrentVehicleLocation;

    private ProgressDialog mProgressDialog;

    private BroadcastReceiver mVehicleReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            if (intent != null) {
                String latitude = intent.getStringExtra(CommonConstants.EXTRA_LATITUDE);
                String longitude = intent.getStringExtra(CommonConstants.EXTRA_LONGITUDE);
                mCurrentVehicleLocation = new LatLng(
                        Double.parseDouble(latitude),
                        Double.parseDouble(longitude));

                mMapFragment.updateVehicleLocation(mCurrentVehicleLocation);
            }
        }
    };

    public static HomeFragment newInstance(int page, String title) {
        Bundle args = new Bundle();
        args.putInt(CommonConstants.PAGE, page);
        args.putString(CommonConstants.TITLE, title);

        HomeFragment fragment = new HomeFragment();
        fragment.setArguments(args);
        return fragment;
    }

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mProgressDialog = new ProgressDialog(getActivity());
        mProgressDialog.setIndeterminate(true);
        mProgressDialog.setCanceledOnTouchOutside(false);
        mProgressDialog.setMessage(getString(R.string.please_wait));
    }

    @Override
    protected int getLayoutResId() {
        return R.layout.fragment_home;
    }

    @Override
    public void onViewCreated(View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        setupMap();

        initViews(view);

        GoogleApiProvider.getInstance().init();
    }

    @Override
    public void onResume() {
        super.onResume();
        // Register vehicle location receiver
        getActivity().registerReceiver(mVehicleReceiver,
                new IntentFilter(CommonConstants.ACTION_RECEIVE_VEHICLE_LOCATION));
    }

    @Override
    public void onPause() {
        super.onPause();
        getActivity().unregisterReceiver(mVehicleReceiver);
    }

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        mMapFragment.onActivityResult(requestCode, resultCode, data);
    }

    @Override
    public void onLicensePlateChange(String licensePlate) {
        super.onLicensePlateChange(licensePlate);
        Intent intent = new Intent(getActivity(), VehicleLocationUpdateService.class);
        intent.setAction(CommonConstants.ACTION_UPDATE_LICENSE_PLATE);
        intent.putExtra(CommonConstants.EXTRA_LICENSE_PLATE, licensePlate);
        getActivity().startService(intent);
    }

    private void setupMap() {
        mMapFragment = new MapFragment();
        Bundle data = new Bundle();
        data.putBoolean(CommonConstants.BUNDLE_MY_LOCATION, true);
        mMapFragment.setArguments(data);
        getFragmentManager().beginTransaction().add(R.id.map_container, mMapFragment).commit();
    }

    private void initViews(View rootView) {
        rootView.findViewById(R.id.fab_vehicle_location).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(getActivity(), VehicleLocationUpdateService.class);
                intent.setAction(CommonConstants.ACTION_GET_CURRENT_VEHICLE_LOCATION);
                getActivity().startService(intent);
            }
        });

        rootView.findViewById(R.id.fab_show_road).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mMapFragment.askForGps(new ResultCallback<LocationSettingsResult>() {
                    @Override
                    public void onResult(@NonNull LocationSettingsResult locationSettingsResult) {
                        final Status status = locationSettingsResult.getStatus();
                        switch (status.getStatusCode()) {
                            case LocationSettingsStatusCodes.SUCCESS:
                                String origin = mMapFragment.getCurrentLocation().latitude + "," + mMapFragment.getCurrentLocation().longitude;
                                String destination = mCurrentVehicleLocation.latitude + "," + mCurrentVehicleLocation.longitude;
                                GoogleApiProvider.getInstance().getDirection(origin, destination,
                                        getString(R.string.server_api_key), new OnServerResponseListener<Route>() {
                                            @Override
                                            public void onSuccess(Route data) {
                                                mMapFragment.drawPaths(data.legs.get(0).steps);
                                            }

                                            @Override
                                            public void onFail(Throwable t) {
                                                showToast(t.getMessage());
                                            }
                                        });
                                break;
                            case LocationSettingsStatusCodes.RESOLUTION_REQUIRED:
                                try {
                                    status.startResolutionForResult(
                                            getActivity(), REQUEST_CODE_GPS);
                                } catch (IntentSender.SendIntentException e) {
                                    e.printStackTrace();
                                }
                                break;
                        }
                    }
                });
            }
        });
    }

    private void showToast(String message) {
        Toast.makeText(getActivity(), message, Toast.LENGTH_SHORT).show();
    }
}
