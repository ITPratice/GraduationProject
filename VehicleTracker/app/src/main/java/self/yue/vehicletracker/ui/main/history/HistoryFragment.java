package self.yue.vehicletracker.ui.main.history;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.util.Log;
import android.view.View;

import java.util.List;

import self.yue.vehicletracker.R;
import self.yue.vehicletracker.base.BasePage;
import self.yue.vehicletracker.data.local.User;
import self.yue.vehicletracker.data.server.ApiProvider;
import self.yue.vehicletracker.util.CommonConstants;
import self.yue.vehicletracker.util.OnServerResponseListener;

/**
 * Created by dongc on 3/25/2017.
 */

public class HistoryFragment extends BasePage {

    public static HistoryFragment newInstance(int page, String title) {
        Bundle args = new Bundle();
        args.putInt(CommonConstants.PAGE, page);
        args.putString(CommonConstants.TITLE, title);

        HistoryFragment fragment = new HistoryFragment();
        fragment.setArguments(args);
        return fragment;
    }

    @Override
    protected int getLayoutResId() {
        return R.layout.fragment_history;
    }

    @Override
    public void onViewCreated(View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        view.findViewById(R.id.btn_get_data).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                ApiProvider.getInstance().getAllUsers(new OnServerResponseListener<List<User>>() {
                    @Override
                    public void onSuccess(List<User> data) {
                        Log.e("Ahihi", "" + data.size());
                    }

                    @Override
                    public void onFail(Throwable t) {
                        Log.e("Ahihi", "" + t.getMessage());
                    }
                });
            }
        });
    }
}
