package self.yue.vehicletracker.base;

import android.app.Fragment;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import self.yue.vehicletracker.util.CommonConstants;

/**
 * Created by dongc on 3/25/2017.
 */

public abstract class BasePage extends Fragment {
    protected int page;
    protected String title;
    protected String licensePlate;

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Bundle data = getArguments();
        if (data != null) {
            page = data.getInt(CommonConstants.PAGE, 0);
            title = data.getString(CommonConstants.TITLE, "");
        }
    }

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container, Bundle savedInstanceState) {
        return inflater.inflate(getLayoutResId(), container, false);
    }

    @Override
    public void onViewCreated(View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
    }

    protected abstract int getLayoutResId();

    public BaseFragmentActivity getBaseFragmentActivity() {
        return (BaseFragmentActivity) getActivity();
    }

    public void onLicensePlateChange(String licensePlate) {
        this.licensePlate = licensePlate;
    }
}
