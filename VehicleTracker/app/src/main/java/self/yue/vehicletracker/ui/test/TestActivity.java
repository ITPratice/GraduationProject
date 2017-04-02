package self.yue.vehicletracker.ui.test;

import self.yue.vehicletracker.base.BaseFragment;
import self.yue.vehicletracker.base.BaseFragmentActivity;

/**
 * Created by dongc on 3/19/2017.
 */

public class TestActivity extends BaseFragmentActivity {
    @Override
    protected BaseFragment getFirstFragment() {
        return new TestSocketFragment();
    }
}
