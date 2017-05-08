package self.yue.vehicletracker.ui.main.history;

import android.app.DatePickerDialog;
import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.view.View;
import android.widget.DatePicker;
import android.widget.TextView;
import android.widget.Toast;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.List;
import java.util.Locale;

import self.yue.vehicletracker.R;
import self.yue.vehicletracker.base.BasePage;
import self.yue.vehicletracker.base.ShowableContent;
import self.yue.vehicletracker.data.local.History;
import self.yue.vehicletracker.data.server.ApiProvider;
import self.yue.vehicletracker.ui.history.HistoryDetailActivity;
import self.yue.vehicletracker.util.CommonConstants;
import self.yue.vehicletracker.util.interfaces.OnRecyclerItemInteractListener;
import self.yue.vehicletracker.util.interfaces.OnServerResponseListener;

/**
 * Created by dongc on 3/25/2017.
 */

public class HistoryFragment extends BasePage implements ShowableContent {
    private TextView mButtonDate;
    private TextView mTextState;
    private View mDataContainer;
    private RecyclerView mRecyclerHistory;

    private List<History> mHistories;
    private HistoryAdapter mAdapter;

    private Calendar mCalendar;

    private DatePickerDialog.OnDateSetListener date = new DatePickerDialog.OnDateSetListener() {
        @Override
        public void onDateSet(DatePicker view, int year, int month, int dayOfMonth) {
            mCalendar.set(Calendar.YEAR, year);
            mCalendar.set(Calendar.MONTH, month);
            mCalendar.set(Calendar.DAY_OF_MONTH, dayOfMonth);

            updateDate();

            fetchData();
        }
    };

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

        initViews(view);

        mCalendar = Calendar.getInstance();
        updateDate();

        mHistories = new ArrayList<>();
        mAdapter = new HistoryAdapter(mHistories);
        mRecyclerHistory.setAdapter(mAdapter);

        mAdapter.setListener(new OnRecyclerItemInteractListener() {
            @Override
            public void onRecyclerItemClick(int position) {
                Bundle data = new Bundle();
                data.putParcelable(CommonConstants.BUNDLE_HISTORY, mHistories.get(position));
                data.putString(CommonConstants.BUNDLE_DATE, mButtonDate.getText().toString());
                data.putString(CommonConstants.BUNDLE_LICENSE_PLATE, licensePlate);
                Intent intent = new Intent(getActivity(), HistoryDetailActivity.class);
                intent.putExtra(CommonConstants.EXTRA_BUNDLE, data);
                startActivity(intent);
            }
        });
    }

    @Override
    public void onResume() {
        super.onResume();
        fetchData();
    }

    @Override
    public void showToast(String message) {
        Toast.makeText(getActivity(), message, Toast.LENGTH_SHORT).show();
    }

    private void initViews(View rootView) {
        mTextState = (TextView) rootView.findViewById(R.id.text_state);
        mDataContainer = rootView.findViewById(R.id.data_container);
        mButtonDate = (TextView) rootView.findViewById(R.id.btn_date);
        mRecyclerHistory = (RecyclerView) rootView.findViewById(R.id.recycler_history);
        mRecyclerHistory.setLayoutManager(new LinearLayoutManager(getActivity()));

        mButtonDate.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new DatePickerDialog(getActivity(), date,
                        mCalendar.get(Calendar.YEAR),
                        mCalendar.get(Calendar.MONTH),
                        mCalendar.get(Calendar.DAY_OF_MONTH)).show();
            }
        });
    }

    private void updateDate() {
        SimpleDateFormat dateFormat = new SimpleDateFormat("dd-MM-yyyy", Locale.getDefault());
        mButtonDate.setText(dateFormat.format(mCalendar.getTime()));
    }

    private void fetchData() {
        ApiProvider.getInstance().getVehicleHistory(licensePlate, mButtonDate.getText().toString(),
                new OnServerResponseListener<List<History>>() {
                    @Override
                    public void onSuccess(List<History> data) {
                        refreshList(data);
                    }

                    @Override
                    public void onFail(Throwable t) {
                        showToast(t.getMessage());
                        showData(mHistories.size() > 0);
                    }
                });
    }

    private void refreshList(List<History> histories) {
        if (histories != null && histories.size() > 0) {
            mHistories.clear();
            mHistories.addAll(histories);
            mAdapter.notifyDataSetChanged();
        } else {
            showData(mHistories.size() > 0);
        }
    }

    private void showData(boolean canShow) {
        if (canShow) {
            mDataContainer.setVisibility(View.VISIBLE);
            mTextState.setVisibility(View.GONE);
        } else {
            mDataContainer.setVisibility(View.GONE);
            mTextState.setVisibility(View.VISIBLE);
        }
    }
}
