package self.yue.vehicletracker.ui.map;

import android.app.Activity;
import android.content.Intent;
import android.content.IntentSender;
import android.graphics.Color;
import android.location.Location;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.util.Log;

import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.common.api.PendingResult;
import com.google.android.gms.common.api.ResultCallback;
import com.google.android.gms.common.api.Status;
import com.google.android.gms.location.LocationListener;
import com.google.android.gms.location.LocationRequest;
import com.google.android.gms.location.LocationServices;
import com.google.android.gms.location.LocationSettingsRequest;
import com.google.android.gms.location.LocationSettingsResult;
import com.google.android.gms.location.LocationSettingsStatusCodes;
import com.google.android.gms.location.places.Places;
import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.OnMapReadyCallback;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.Marker;
import com.google.android.gms.maps.model.MarkerOptions;
import com.google.android.gms.maps.model.Polyline;
import com.google.android.gms.maps.model.PolylineOptions;

import java.util.ArrayList;
import java.util.List;

import self.yue.vehicletracker.R;
import self.yue.vehicletracker.data.local.google.Step;
import self.yue.vehicletracker.util.BitmapHelper;
import self.yue.vehicletracker.util.CacheHelper;
import self.yue.vehicletracker.util.CommonConstants;
import self.yue.vehicletracker.util.PermissionChecker;

/**
 * Created by dongc on 3/25/2017.
 */

public class MapFragment extends com.google.android.gms.maps.MapFragment implements OnMapReadyCallback,
        GoogleApiClient.OnConnectionFailedListener, GoogleApiClient.ConnectionCallbacks, LocationListener {
    public static final int REQUEST_CODE_GPS = 1000;

    private static final int DEFAULT_ZOOM = 15;
    private static final long UPDATE_INTERVAL = 10000;
    private static final long FASTEST_UPDATE_INTERVAL =
            UPDATE_INTERVAL / 2;
    private static final int CONNECTION_FAILURE_RESOLUTION_REQUEST = 532;
    private static final String TAG = MapFragment.class.getSimpleName();

    private GoogleMap mMap;
    private GoogleApiClient mGoogleApiClient;
    private Location mLastKnownLocation;
    private LocationRequest mLocationRequest;
    private LocationSettingsRequest.Builder mLocationSettingBuilder;
    private LatLng mDefaultLocation;
    private Marker mVehicleMarker;
    private Marker mStartMarker;
    private Marker mEndMarker;
    private List<Polyline> mPolylines;

    private boolean mEnableMyLocation;

    public MapFragment() {
        mDefaultLocation = new LatLng(21.048647, 105.784634); // Military technical academy
    }

    @Override
    public void onCreate(Bundle bundle) {
        super.onCreate(bundle);

        getMapAsync(this);

        createLocationRequest();

        mPolylines = new ArrayList<>();

        Bundle data = getArguments();
        if (data != null) {
            mEnableMyLocation = data.getBoolean(CommonConstants.BUNDLE_MY_LOCATION);
        }
    }

    @Override
    public void onResume() {
        super.onResume();
        if (mGoogleApiClient != null && !mGoogleApiClient.isConnected())
            mGoogleApiClient.connect();
    }

    @Override
    public void onStop() {
        super.onStop();
        CacheHelper.getInstance().saveCameraPosition(mMap.getCameraPosition());
        Log.e("Map Fragment", "Ahuhu");
        if (mGoogleApiClient.isConnected()) {
            LocationServices.FusedLocationApi.removeLocationUpdates(mGoogleApiClient, this);
            mGoogleApiClient.disconnect();
        }
    }

    @Override
    public void onMapReady(GoogleMap googleMap) {
        mMap = googleMap;

        // Setup google api client
        mGoogleApiClient = new GoogleApiClient.Builder(getActivity())
                .addConnectionCallbacks(this)
                .addOnConnectionFailedListener(this)
                .addApi(LocationServices.API)
                .addApi(Places.GEO_DATA_API)
                .addApi(Places.PLACE_DETECTION_API)
                .build();
        mGoogleApiClient.connect();
    }

    @Override
    public void onConnectionFailed(@NonNull ConnectionResult connectionResult) {
        if (connectionResult.hasResolution()) {
            try {
                connectionResult.startResolutionForResult(getActivity(),
                        CONNECTION_FAILURE_RESOLUTION_REQUEST);
            } catch (IntentSender.SendIntentException e) {
                e.printStackTrace();
            }
        } else
            Log.e(TAG, "Location services connection failed with code " + connectionResult.getErrorCode());
    }

    @Override
    public void onConnected(@Nullable Bundle bundle) {
        if (mLocationSettingBuilder == null) {
            mLocationSettingBuilder = new LocationSettingsRequest.Builder()
                    .addLocationRequest(mLocationRequest);
            mLocationSettingBuilder.setAlwaysShow(true);
        }

        if (mEnableMyLocation) {
            askForGps(new ResultCallback<LocationSettingsResult>() {
                @Override
                public void onResult(@NonNull LocationSettingsResult locationSettingsResult) {
                    final Status status = locationSettingsResult.getStatus();
                    switch (status.getStatusCode()) {
                        case LocationSettingsStatusCodes.SUCCESS:
                            updateLocationUI();
                            getDeviceLocation();
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
    }

    @Override
    public void onConnectionSuspended(int i) {

    }

    @Override
    public void onLocationChanged(Location location) {
        if (mEnableMyLocation) {
            mLastKnownLocation = location;
            updatePosition(location);
        }
    }

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == REQUEST_CODE_GPS) {
            if (resultCode == Activity.RESULT_OK) {
                updateLocationUI();
                getDeviceLocation();
            } else {
                getDeviceLocation();
            }
        }
    }

    public void askForGps(ResultCallback<LocationSettingsResult> callback) {
        PendingResult<LocationSettingsResult> result = LocationServices.SettingsApi
                .checkLocationSettings(mGoogleApiClient, mLocationSettingBuilder.build());
        result.setResultCallback(callback);
    }

    public void updateVehicleLocation(LatLng position) {
        if (mVehicleMarker != null)
            mVehicleMarker.remove();
        mVehicleMarker = mMap.addMarker(new MarkerOptions().position(position).title("Your vehicle")
                .icon(BitmapHelper.getBitmapDescriptor(getActivity(), R.drawable.ic_wheel)));
        mMap.animateCamera(CameraUpdateFactory.newLatLngZoom(position, 15));
    }

    public LatLng getCurrentLocation() {
        return mLastKnownLocation != null
                ? new LatLng(mLastKnownLocation.getLatitude(), mLastKnownLocation.getLongitude())
                : mDefaultLocation;
    }

    public void drawPaths(List<Step> steps) {
        if (steps.size() > 0) {
            // Remove old lines
            if (mPolylines.size() > 0) {
                for (Polyline polyline : mPolylines) {
                    polyline.remove();
                }
                mPolylines.clear();
            }

            for (Step step : steps) {
                List<LatLng> points = decodePoints(step.polyline.points);
                PolylineOptions polylineOptions = new PolylineOptions();
                polylineOptions.addAll(points);
                polylineOptions.width(3);
                polylineOptions.color(Color.BLUE);

                Polyline polyline = mMap.addPolyline(polylineOptions);
                mPolylines.add(polyline);
            }
        }
    }

    public void moveCameraTo(LatLng position, int zoomLevel) {
        mMap.animateCamera(CameraUpdateFactory.newLatLngZoom(position, zoomLevel));
    }

    public void addStartMarker(LatLng position) {
        if (mStartMarker != null) {
            mStartMarker.remove();
        }
        mStartMarker = mMap.addMarker(new MarkerOptions().position(position).title("Start position")
                .icon(BitmapHelper.getBitmapDescriptor(getActivity(), R.drawable.ic_wheel)));
    }

    public void addEndMarker(LatLng position) {
        if (mEndMarker != null) {
            mEndMarker.remove();
        }
        mEndMarker = mMap.addMarker(new MarkerOptions().position(position).title("End position")
                .icon(BitmapHelper.getBitmapDescriptor(getActivity(), R.drawable.ic_wheel)));
    }

    private void updateLocationUI() {
        if (mEnableMyLocation) {
            if (PermissionChecker.checkLocationPermission(getActivity())) {
                mMap.setMyLocationEnabled(true);
                mMap.getUiSettings().setMyLocationButtonEnabled(true);
            } else {
                mMap.setMyLocationEnabled(false);
                mMap.getUiSettings().setMyLocationButtonEnabled(false);
            }
        }
    }

    private void getDeviceLocation() {
        if (PermissionChecker.checkLocationPermission(getActivity())) {
            mLastKnownLocation = LocationServices.FusedLocationApi.getLastLocation(mGoogleApiClient);
        }

        if (mLastKnownLocation != null) {
            mMap.animateCamera(CameraUpdateFactory.newLatLngZoom(
                    new LatLng(mLastKnownLocation.getLatitude(), mLastKnownLocation.getLongitude()),
                    DEFAULT_ZOOM
            ));
        } else {
            LatLng latLng = CacheHelper.getInstance().getLastPosition();
            if (latLng == null) {
                mMap.animateCamera(CameraUpdateFactory.zoomBy(5));
            } else {
                mMap.animateCamera(CameraUpdateFactory.newLatLngZoom(latLng, DEFAULT_ZOOM));
            }
        }
    }

    private void updatePosition(Location location) {
        mMap.animateCamera(CameraUpdateFactory.newLatLngZoom(
                new LatLng(location.getLatitude(), location.getLongitude()),
                DEFAULT_ZOOM
        ));
    }

    private void createLocationRequest() {
        mLocationRequest = new LocationRequest();
        mLocationRequest.setInterval(UPDATE_INTERVAL);
        mLocationRequest.setFastestInterval(FASTEST_UPDATE_INTERVAL);
        mLocationRequest.setPriority(LocationRequest.PRIORITY_HIGH_ACCURACY);
    }

    private List<LatLng> decodePoints(String encodedPoints) {
        List<LatLng> poly = new ArrayList<>();
        int index = 0, len = encodedPoints.length();
        int lat = 0, lng = 0;

        while (index < len) {
            int b, shift = 0, result = 0;
            do {
                b = encodedPoints.charAt(index++) - 63;
                result |= (b & 0x1f) << shift;
                shift += 5;
            } while (b >= 0x20);
            int dlat = ((result & 1) != 0 ? ~(result >> 1) : (result >> 1));
            lat += dlat;

            shift = 0;
            result = 0;
            do {
                b = encodedPoints.charAt(index++) - 63;
                result |= (b & 0x1f) << shift;
                shift += 5;
            } while (b >= 0x20);
            int dlng = ((result & 1) != 0 ? ~(result >> 1) : (result >> 1));
            lng += dlng;

            LatLng p = new LatLng((((double) lat / 1E5)),
                    (((double) lng / 1E5)));
            poly.add(p);
        }

        return poly;
    }
}
