package self.yue.vehicletracker.ui.history;

import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.content.ContextCompat;
import android.support.v7.widget.Toolbar;
import android.text.TextUtils;
import android.view.MenuItem;
import android.widget.TextView;

import com.google.android.gms.maps.model.LatLng;

import butterknife.BindView;
import butterknife.ButterKnife;
import self.yue.vehicletracker.R;
import self.yue.vehicletracker.base.BaseActivity;
import self.yue.vehicletracker.data.local.ServerHistory;
import self.yue.vehicletracker.data.local.google.Route;
import self.yue.vehicletracker.data.server.GoogleApiProvider;
import self.yue.vehicletracker.ui.map.MapFragment;
import self.yue.vehicletracker.util.CommonConstants;
import self.yue.vehicletracker.util.interfaces.OnServerResponseListener;

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

    private MapFragment mMapFragment;
    private ServerHistory mServerHistory;

    private String mDate;
    private String mLicensePlate;

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

        showPath();
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
                mServerHistory = data.getParcelable(CommonConstants.BUNDLE_HISTORY);
                mDate = data.getString(CommonConstants.BUNDLE_DATE);
                mLicensePlate = data.getString(CommonConstants.BUNDLE_LICENSE_PLATE);
            }
        }
    }

    private void initViews() {
        mTextStartLocation.setSelected(true);
        mTextStartLocation.setHorizontallyScrolling(true);

        mTextEndLocation.setSelected(true);
        mTextEndLocation.setHorizontallyScrolling(true);

        mTextStartTime.setText(TextUtils.isEmpty(mServerHistory.startTime) ?
                getString(R.string.unknown) :
                mServerHistory.startTime);

        mTextEndTime.setText(TextUtils.isEmpty(mServerHistory.endTime) ?
                getString(R.string.unknown) :
                mServerHistory.endTime);

        mTextDate.setText(mDate);
    }

    private void setupMap() {
        mMapFragment = new MapFragment();
        Bundle data = new Bundle();
        data.putBoolean(CommonConstants.BUNDLE_MY_LOCATION, false);
        mMapFragment.setArguments(data);
        getFragmentManager().beginTransaction().add(R.id.map_container, mMapFragment).commit();
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
        String origin = "21.087058,105.804273";
        String destination = "21.048165,105.786281";

        GoogleApiProvider.getInstance().getDirection(origin, destination,
                getString(R.string.server_api_key), new OnServerResponseListener<Route>() {
                    @Override
                    public void onSuccess(Route data) {
                        mMapFragment.moveCameraTo(new LatLng(21.087058, 105.804273), 13);
                        mMapFragment.addStartMarker(new LatLng(21.087058, 105.804273));
                        mMapFragment.addEndMarker(new LatLng(21.048165, 105.786281));
                        mMapFragment.drawPaths(data.legs.get(0).steps);
                    }

                    @Override
                    public void onFail(Throwable t) {
                    }
                });
    }
}
