package self.yue.vehicletracker.ui.main;

import android.app.Fragment;
import android.app.FragmentManager;
import android.support.v13.app.FragmentPagerAdapter;

import self.yue.vehicletracker.ui.main.history.HistoryFragment;
import self.yue.vehicletracker.ui.main.home.HomeFragment;
import self.yue.vehicletracker.ui.main.more.MoreFragment;
import self.yue.vehicletracker.util.CommonConstants;

/**
 * Created by dongc on 3/25/2017.
 */

public class MainPagerAdapter extends FragmentPagerAdapter {
    private static final int NUMBER_OF_PAGES = 3;

    public MainPagerAdapter(FragmentManager fm) {
        super(fm);
    }

    @Override
    public Fragment getItem(int position) {
        switch (position) {
            case 0:
                return HomeFragment.newInstance(CommonConstants.INDEX_HOME_PAGE, "Home");
            case 1:
                return HistoryFragment.newInstance(CommonConstants.INDEX_HISTORY_PAGE, "History");
            case 2:
                return MoreFragment.newInstance(CommonConstants.INDEX_MORE_PAGE, "More");
            default:
                return null;
        }
    }

    @Override
    public int getCount() {
        return NUMBER_OF_PAGES;
    }
}
