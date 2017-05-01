package self.yue.vehicletracker.ui.main;

import android.content.Intent;

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

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        getCurrentFragment().onActivityResult(requestCode, resultCode, data);
    }
}
