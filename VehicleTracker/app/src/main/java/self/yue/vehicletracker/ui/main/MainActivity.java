package self.yue.vehicletracker.ui.main;

import self.yue.vehicletracker.base.BaseFragment;
import self.yue.vehicletracker.base.BaseFragmentActivity;

/**
 * Created by dongc on 3/25/2017.
 */

public class MainActivity extends BaseFragmentActivity {
    @Override
    protected BaseFragment getFirstFragment() {
        return new MainFragment();
    }
}
