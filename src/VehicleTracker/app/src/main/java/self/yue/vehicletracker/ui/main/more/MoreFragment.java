package self.yue.vehicletracker.ui.main.more;

import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.widget.SwitchCompat;
import android.view.View;
import android.widget.CompoundButton;
import android.widget.TextView;
import android.widget.Toast;

import self.yue.vehicletracker.R;
import self.yue.vehicletracker.base.BasePage;
import self.yue.vehicletracker.base.ShowableContent;
import self.yue.vehicletracker.data.local.Vehicle;
import self.yue.vehicletracker.data.server.ApiProvider;
import self.yue.vehicletracker.ui.login.LoginActivity;
import self.yue.vehicletracker.ui.profile.UpdateProfileActivity;
import self.yue.vehicletracker.ui.widgets.ChangePasswordDialog;
import self.yue.vehicletracker.util.CacheHelper;
import self.yue.vehicletracker.util.CommonConstants;
import self.yue.vehicletracker.util.interfaces.OnServerResponseListener;

/**
 * Created by dongc on 3/25/2017.
 */

public class MoreFragment extends BasePage implements ShowableContent {
    private SwitchCompat mSwitchWriteHistory;
    private TextView mTextName;

    private Vehicle mCurrentVehicle;

    public static MoreFragment newInstance(int page, String title) {
        Bundle args = new Bundle();
        args.putInt(CommonConstants.PAGE, page);
        args.putString(CommonConstants.TITLE, title);

        MoreFragment fragment = new MoreFragment();
        fragment.setArguments(args);
        return fragment;
    }

    @Override
    protected int getLayoutResId() {
        return R.layout.fragment_more;
    }

    @Override
    public void onViewCreated(View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        initViews(view);
        mTextName.setText(CacheHelper.getInstance().getCurrentUser().getName());
    }

    @Override
    public void onLicensePlateChange(String licensePlate) {
        super.onLicensePlateChange(licensePlate);
        ApiProvider.getInstance().getVehicle(licensePlate, new OnServerResponseListener<Vehicle>() {
            @Override
            public void onSuccess(Vehicle data) {
                mCurrentVehicle = data;
                mSwitchWriteHistory.setChecked(mCurrentVehicle.writeHistory == 1);
            }

            @Override
            public void onFail(Throwable t) {
                showToast(t.getMessage());
            }
        });
    }

    @Override
    public void showToast(String message) {
        Toast.makeText(getActivity(), message, Toast.LENGTH_SHORT).show();
    }

    private void initViews(View rootView) {
        mTextName = (TextView) rootView.findViewById(R.id.text_name);
        mSwitchWriteHistory = (SwitchCompat) rootView.findViewById(R.id.switch_write_history);

        // Button logout
        rootView.findViewById(R.id.btn_logout).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                getActivity().onBackPressed();
            }
        });

        rootView.findViewById(R.id.btn_change_password).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ChangePasswordDialog dialog = new ChangePasswordDialog(getActivity());
                dialog.setOnDialogButtonClickListener(new ChangePasswordDialog.OnDialogButtonClickListener() {
                    @Override
                    public void onPositiveButtonClicked() {
                        startActivity(new Intent(getActivity(), LoginActivity.class));
                        getActivity().finish();
                    }
                });
                dialog.show();
            }
        });

        rootView.findViewById(R.id.btn_edit_profile).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(new Intent(getActivity(), UpdateProfileActivity.class));
            }
        });

        mSwitchWriteHistory.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                mCurrentVehicle.writeHistory = isChecked ? 1 : 0;
                ApiProvider.getInstance().updateVehicleState(mCurrentVehicle,
                        new OnServerResponseListener<String>() {
                            @Override
                            public void onSuccess(String data) {
                                showToast("Update successfully!");
                            }

                            @Override
                            public void onFail(Throwable t) {
                                mCurrentVehicle.writeHistory = mCurrentVehicle.writeHistory == 1 ? 0 : 1;
                                mSwitchWriteHistory.setChecked(mCurrentVehicle.writeHistory == 1);
                                showToast(t.getMessage());
                            }
                        });
            }
        });
    }
}
