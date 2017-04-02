package self.yue.vehicletracker.base;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.widget.Toolbar;

import self.yue.vehicletracker.R;

/**
 * Created by dongc on 3/18/2017.
 */

public abstract class BaseFragmentActivity extends BaseActivity {
    private Toolbar mToolbar;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Setup toolbar
        mToolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(mToolbar);

        // Add fragment
        getFragmentManager().beginTransaction().add(R.id.fragment_container, getFirstFragment()).commit();
    }

    @Override
    protected int getLayoutResId() {
        return R.layout.activity_fragment_base;
    }

    protected abstract BaseFragment getFirstFragment();
}
