package self.yue.vehicletracker.base;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.content.ContextCompat;
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

        if (savedInstanceState == null) {
            // Setup toolbar
            mToolbar = (Toolbar) findViewById(R.id.toolbar);
            setSupportActionBar(mToolbar);
            getSupportActionBar().setDisplayShowTitleEnabled(false);
            mToolbar.setTitleTextColor(ContextCompat.getColor(this, R.color.white));

            // Add fragment
            getFragmentManager().beginTransaction().add(R.id.fragment_container, getFirstFragment()).commit();
        }
    }

    @Override
    protected int getLayoutResId() {
        return R.layout.activity_fragment_base;
    }

    protected abstract BaseFragment getFirstFragment();

    public BaseFragment getCurrentFragment() {
        return (BaseFragment) getFragmentManager().findFragmentById(R.id.fragment_container);
    }

    public Toolbar getToolbar() {
        return mToolbar;
    }
}
