package self.yue.vehicletracker.ui.history;

import android.content.Intent;
import android.location.Address;
import android.location.Geocoder;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.content.ContextCompat;
import android.support.v7.widget.Toolbar;
import android.text.TextUtils;
import android.view.MenuItem;
import android.widget.TextView;

import com.google.android.gms.maps.model.LatLng;

import java.io.IOException;
import java.util.List;
import java.util.Locale;

import butterknife.BindView;
import butterknife.ButterKnife;
import self.yue.vehicletracker.R;
import self.yue.vehicletracker.base.BaseActivity;
import self.yue.vehicletracker.data.local.History;
import self.yue.vehicletracker.ui.map.MapFragment;
import self.yue.vehicletracker.util.CommonConstants;

/**
 * Created by dongc on 5/6/2017.
 */

public class HistoryDetailActivity extends BaseActivity {
    @BindView(R.id.text_start_location)
    TextView mTextStartLocation;
    @BindView(R.id.text_end_location)
    TextView mTextEndLocation;
    @BindView(R.id.text_start_time)
    TextView mTextStartTime;
    @BindView(R.id.text_end_time)
    TextView mTextEndTime;
    @BindView(R.id.text_date)
    TextView mTextDate;
    @BindView(R.id.toolbar)
    Toolbar mToolbar;

    private Geocoder mGeocoder;

    private MapFragment mMapFragment;
    private History mHistory;

    private String mDate;
    private String mLicensePlate;

    private LatLng mStartPosition;
    private LatLng mEndPosition;

    @Override
    protected int getLayoutResId() {
        return R.layout.activity_history_detail;
    }

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        ButterKnife.bind(this);

        getData();
        initViews();
        setupMap();
        setupToolbar();

        mGeocoder = new Geocoder(this, Locale.getDefault());
        getLocationAddress(mStartPosition.latitude, mStartPosition.longitude, true);
        getLocationAddress(mEndPosition.latitude, mEndPosition.longitude, false);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        if (item.getItemId() == android.R.id.home) {
            onBackPressed();
        }
        return super.onOptionsItemSelected(item);
    }

    private void getData() {
        Intent intent = getIntent();
        if (intent != null) {
            Bundle data = intent.getBundleExtra(CommonConstants.EXTRA_BUNDLE);
            if (data != null) {
                mHistory = data.getParcelable(CommonConstants.BUNDLE_HISTORY);
                mDate = data.getString(CommonConstants.BUNDLE_DATE);
                mLicensePlate = data.getString(CommonConstants.BUNDLE_LICENSE_PLATE);
            }
        }

        mStartPosition = new LatLng(Double.parseDouble(mHistory.locations.get(0).latitude),
                Double.parseDouble(mHistory.locations.get(0).longitude));
        mEndPosition = new LatLng(Double.parseDouble(mHistory.locations.get(mHistory.locations.size() - 1).latitude),
                Double.parseDouble(mHistory.locations.get(mHistory.locations.size() - 1).longitude));
    }

    private void initViews() {
        mTextStartLocation.setSelected(true);
        mTextStartLocation.setHorizontallyScrolling(true);

        mTextEndLocation.setSelected(true);
        mTextEndLocation.setHorizontallyScrolling(true);

        mTextStartTime.setText(TextUtils.isEmpty(mHistory.startTime) ?
                getString(R.string.unknown) :
                mHistory.startTime);

        mTextEndTime.setText(TextUtils.isEmpty(mHistory.endTime) ?
                getString(R.string.unknown) :
                mHistory.endTime);

        mTextDate.setText(mDate);
    }

    private void setupMap() {
        mMapFragment = new MapFragment();
        Bundle data = new Bundle();
        data.putBoolean(CommonConstants.BUNDLE_MY_LOCATION, false);
        mMapFragment.setArguments(data);
        getFragmentManager().beginTransaction().add(R.id.map_container, mMapFragment).commit();

        mMapFragment.setOnMapReadyListener(new MapFragment.OnMapReadyListener() {
            @Override
            public void onMapReady() {
                showPath();
            }
        });
    }

    private void setupToolbar() {
        setSupportActionBar(mToolbar);
        getSupportActionBar().setDisplayShowTitleEnabled(false);
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);
        getSupportActionBar().setHomeAsUpIndicator(R.drawable.ic_close);
        mToolbar.setTitle(mLicensePlate);
        mToolbar.setTitleTextColor(ContextCompat.getColor(this, R.color.white));
    }

    private void showPath() {
        mMapFragment.moveCameraTo(mStartPosition, 13);
        mMapFragment.addStartMarker(mStartPosition);
        mMapFragment.addEndMarker(mEndPosition);
        mMapFragment.drawPath(mHistory.locations);
    }

    private void getLocationAddress(double latitude, double longitude, final boolean isStartLocation) {
        new AsyncTask<LatLng, Void, Address>() {
            @Override
            protected Address doInBackground(LatLng... params) {
                try {
                    List<Address> addresses = mGeocoder
                            .getFromLocation(params[0].latitude, params[0].longitude, 1);
                    if (addresses != null && addresses.size() > 0)
                        return addresses.get(0);
                } catch (IOException e) {
                    e.printStackTrace();
                }
                return null;
            }

            @Override
            protected void onPostExecute(Address address) {
                if (address != null) {
                    String addressText = String.format("%s",
                            address.getMaxAddressLineIndex() > 0 ? address.getAddressLine(0) :
                                    getString(R.string.unknown_location));
                    if (isStartLocation) {
                        mTextStartLocation.setText(addressText);
                    } else {
                        mTextEndLocation.setText(addressText);
                    }
                } else {
                    if (isStartLocation) {
                        mTextStartLocation.setText("Unknown location");
                    } else {
                        mTextEndLocation.setText("Unknown location");
                    }
                }
            }
        }.execute(new LatLng(latitude, longitude));
    }
}
