package self.yue.vehicletracker.ui.main.home;

import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.util.Log;
import android.view.View;

import self.yue.vehicletracker.R;
import self.yue.vehicletracker.base.BasePage;
import self.yue.vehicletracker.util.CommonConstants;

/**
 * Created by dongc on 3/25/2017.
 */

public class HomeFragment extends BasePage {
    private CogiloMapFragment mMapFragment;

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
    }

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        Log.e(HomeFragment.class.getSimpleName(), "" + requestCode);
        mMapFragment.onActivityResult(requestCode, resultCode, data);
    }

    private void setupMap() {
        mMapFragment = new CogiloMapFragment();
        getFragmentManager().beginTransaction().add(R.id.map_container, mMapFragment).commit();
    }
}
