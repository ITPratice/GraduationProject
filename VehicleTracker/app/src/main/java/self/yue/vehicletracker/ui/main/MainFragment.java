package self.yue.vehicletracker.ui.main;

import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.design.widget.BottomNavigationView;
import android.support.v4.view.ViewPager;
import android.view.MenuItem;
import android.view.View;

import self.yue.vehicletracker.R;
import self.yue.vehicletracker.base.BaseFragment;
import self.yue.vehicletracker.util.CommonConstants;

/**
 * Created by dongc on 3/25/2017.
 */

public class MainFragment extends BaseFragment {
    private ViewPager mPager;
    private BottomNavigationView mBottomBar;

    private MainPagerAdapter mAdapter;

    @Override
    protected int getLayoutResId() {
        return R.layout.fragment_main;
    }

    @Override
    public void onViewCreated(View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        initViews(view);
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
                switch (position) {
                    case CommonConstants.INDEX_HOME_PAGE:
                        mBottomBar.setSelectedItemId(R.id.action_home);
                        break;
                    case CommonConstants.INDEX_HISTORY_PAGE:
                        mBottomBar.setSelectedItemId(R.id.action_history);
                        break;
                    case CommonConstants.INDEX_MORE_PAGE:
                        mBottomBar.setSelectedItemId(R.id.action_more);
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
}
