package self.yue.vehicletracker.ui.main.history;

import android.app.DatePickerDialog;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.widget.RecyclerView;
import android.view.View;
import android.widget.DatePicker;
import android.widget.TextView;

import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Locale;

import self.yue.vehicletracker.R;
import self.yue.vehicletracker.base.BasePage;
import self.yue.vehicletracker.util.CommonConstants;

/**
 * Created by dongc on 3/25/2017.
 */

public class HistoryFragment extends BasePage {
    private TextView mButtonDate;
    private RecyclerView mRecyclerHistory;

    private Calendar mCalendar;

    private DatePickerDialog.OnDateSetListener date = new DatePickerDialog.OnDateSetListener() {
        @Override
        public void onDateSet(DatePicker view, int year, int month, int dayOfMonth) {
            mCalendar.set(Calendar.YEAR, year);
            mCalendar.set(Calendar.MONTH, month);
            mCalendar.set(Calendar.DAY_OF_MONTH, dayOfMonth);

            updateDate();
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
    }

    private void initViews(View rootView) {
        mButtonDate = (TextView) rootView.findViewById(R.id.btn_date);
        mRecyclerHistory = (RecyclerView) rootView.findViewById(R.id.recycler_history);

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
        SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy", Locale.getDefault());
        mButtonDate.setText(dateFormat.format(mCalendar.getTime()));
    }
}
