package self.yue.vehicletracker.ui.main.home;

import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.util.Log;
import android.view.View;

import com.google.android.gms.maps.model.LatLng;

import self.yue.vehicletracker.R;
import self.yue.vehicletracker.base.BasePage;
import self.yue.vehicletracker.data.local.google.Route;
import self.yue.vehicletracker.data.server.GoogleApiProvider;
import self.yue.vehicletracker.util.CommonConstants;
import self.yue.vehicletracker.util.OnServerResponseListener;

/**
 * Created by dongc on 3/25/2017.
 */

public class HomeFragment extends BasePage {
    private MapFragment mMapFragment;

    public static HomeFragment newInstance(int page, String title) {
        Bundle args = new Bundle();
        args.putInt(CommonConstants.PAGE, page);
        args.putString(CommonConstants.TITLE, title);

        HomeFragment fragment = new HomeFragment();
        fragment.setArguments(args);
        return fragment;
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
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        mMapFragment.onActivityResult(requestCode, resultCode, data);
    }

    private void setupMap() {
        mMapFragment = new MapFragment();
        getFragmentManager().beginTransaction().add(R.id.map_container, mMapFragment).commit();
    }

    private void initViews(View rootView) {
        rootView.findViewById(R.id.fab_vehicle_location).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mMapFragment.updateVehicleLocation(new LatLng(21.048647, 105.784634));
            }
        });

        rootView.findViewById(R.id.fab_show_road).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String origin = mMapFragment.getCurrentLocation().latitude + "," + mMapFragment.getCurrentLocation().longitude;
                String destination = "21.048647,105.784634";
                GoogleApiProvider.getInstance().getDirection(origin, destination,
                        getString(R.string.server_api_key), new OnServerResponseListener<Route>() {
                            @Override
                            public void onSuccess(Route data) {
                                Log.e("Ahihi", "" + data.legs.size());
                                mMapFragment.drawPaths(data.legs.get(0).steps);
                            }

                            @Override
                            public void onFail(Throwable t) {

                            }
                        });
            }
        });
    }
}
