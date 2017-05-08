package self.yue.vehicletracker.ui.main;

import android.app.Fragment;
import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.design.widget.BottomNavigationView;
import android.support.v4.view.MenuItemCompat;
import android.support.v4.view.ViewPager;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Spinner;

import java.util.List;

import self.yue.vehicletracker.R;
import self.yue.vehicletracker.base.BaseFragment;
import self.yue.vehicletracker.base.BasePage;
import self.yue.vehicletracker.data.local.Vehicle;
import self.yue.vehicletracker.data.server.ApiProvider;
import self.yue.vehicletracker.util.CacheHelper;
import self.yue.vehicletracker.util.CommonConstants;
import self.yue.vehicletracker.util.interfaces.OnServerResponseListener;

/**
 * Created by dongc on 3/25/2017.
 */

public class MainFragment extends BaseFragment {
    private ViewPager mPager;
    private BottomNavigationView mBottomBar;
    private MenuItem mSpinnerItem;

    private MainPagerAdapter mAdapter;

    private ArrayAdapter<String> mVehiclesAdapter;

    private String mLicensePlate;

    @Override
    protected int getLayoutResId() {
        return R.layout.fragment_main;
    }

    @Override
    public void onViewCreated(View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        initViews(view);
        getBaseFragmentActivity().getToolbar().setTitle("Home");

        mVehiclesAdapter = new ArrayAdapter<>(getActivity(), android.R.layout.simple_spinner_item);
        mVehiclesAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
    }

    @Override
    public void onResume() {
        super.onResume();
    }

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        Fragment fragment = getFragmentManager()
                .findFragmentByTag("android:switcher:" + R.id.view_pager + ":" + mPager.getCurrentItem());
        fragment.onActivityResult(requestCode, resultCode, data);
    }

    @Override
    public void onCreateOptionsMenu(Menu menu, MenuInflater inflater) {
        inflater.inflate(R.menu.menu_main, menu);
        mSpinnerItem = menu.findItem(R.id.action_number_plate);

        Spinner spinnerNumberPlate = (Spinner) MenuItemCompat.getActionView(mSpinnerItem);

        spinnerNumberPlate.setAdapter(mVehiclesAdapter);

        ApiProvider.getInstance().getUserVehicles(CacheHelper.getInstance().getCurrentUser().getEmail(),
                new OnServerResponseListener<List<Vehicle>>() {
                    @Override
                    public void onSuccess(List<Vehicle> data) {
                        for (Vehicle vehicle : data) {
                            mVehiclesAdapter.add(vehicle.licensePlate);
                        }
                        mVehiclesAdapter.notifyDataSetChanged();

                        if (data.size() > 0) {
                            mLicensePlate = data.get(0).licensePlate;
                            transferDataToPage();
                        }
                    }

                    @Override
                    public void onFail(Throwable t) {

                    }
                });

        spinnerNumberPlate.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                mLicensePlate = mVehiclesAdapter.getItem(position);
                transferDataToPage();
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {

            }
        });
    }

    private void initViews(View rootView) {
        // Init view pager and it's adapter
        mPager = (ViewPager) rootView.findViewById(R.id.view_pager);
        mAdapter = new MainPagerAdapter(getFragmentManager());
        mPager.setAdapter(mAdapter);
        mPager.addOnPageChangeListener(new ViewPager.OnPageChangeListener() {
            @Override
            public void onPageScrolled(int position, float positionOffset, int positionOffsetPixels) {

            }

            @Override
            public void onPageSelected(int position) {
                transferDataToPage();

                switch (position) {
                    case CommonConstants.INDEX_HOME_PAGE:
                        mBottomBar.setSelectedItemId(R.id.action_home);
                        getBaseFragmentActivity().getToolbar().setTitle("Home");
                        mSpinnerItem.setVisible(true);
                        transferDataToPage();
                        break;
                    case CommonConstants.INDEX_HISTORY_PAGE:
                        mBottomBar.setSelectedItemId(R.id.action_history);
                        getBaseFragmentActivity().getToolbar().setTitle("ServerHistory");
                        mSpinnerItem.setVisible(true);
                        transferDataToPage();
                        break;
                    case CommonConstants.INDEX_MORE_PAGE:
                        mBottomBar.setSelectedItemId(R.id.action_more);
                        getBaseFragmentActivity().getToolbar().setTitle("More");
                        mSpinnerItem.setVisible(true);
                        break;
                }
            }

            @Override
            public void onPageScrollStateChanged(int state) {

            }
        });

        // Init bottom barF
        mBottomBar = (BottomNavigationView) rootView.findViewById(R.id.bottom_bar);
        mBottomBar.setOnNavigationItemSelectedListener(new BottomNavigationView.OnNavigationItemSelectedListener() {
            @Override
            public boolean onNavigationItemSelected(@NonNull MenuItem item) {
                switch (item.getItemId()) {
                    case R.id.action_home:
                        mPager.setCurrentItem(CommonConstants.INDEX_HOME_PAGE, true);
                        break;
                    case R.id.action_history:
                        mPager.setCurrentItem(CommonConstants.INDEX_HISTORY_PAGE, true);
                        break;
                    case R.id.action_more:
                        mPager.setCurrentItem(CommonConstants.INDEX_MORE_PAGE, true);
                        break;
                }
                return true;
            }
        });
    }

    private void transferDataToPage() {
        BasePage page = (BasePage) getFragmentManager()
                .findFragmentByTag("android:switcher:" + R.id.view_pager + ":" + mPager.getCurrentItem());
        page.onLicensePlateChange(mLicensePlate);
    }
}
