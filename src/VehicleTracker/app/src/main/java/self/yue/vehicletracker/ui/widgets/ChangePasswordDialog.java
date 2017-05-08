package self.yue.vehicletracker.ui.widgets;

import android.app.Dialog;
import android.app.ProgressDialog;
import android.content.Context;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.text.TextUtils;
import android.view.Window;
import android.widget.EditText;
import android.widget.Toast;

import butterknife.BindView;
import butterknife.ButterKnife;
import butterknife.OnClick;
import self.yue.vehicletracker.R;
import self.yue.vehicletracker.data.local.User;
import self.yue.vehicletracker.data.server.ApiProvider;
import self.yue.vehicletracker.util.CacheHelper;
import self.yue.vehicletracker.util.interfaces.OnServerResponseListener;

/**
 * Created by dongc on 5/4/2017.
 */

public class ChangePasswordDialog extends Dialog {
    @BindView(R.id.edit_old_password)
    EditText mEditOldPassword;

    @BindView(R.id.edit_new_password)
    EditText mEditNewPassword;

    private ProgressDialog mProgressDialog;

    private OnDialogButtonClickListener mListener;

    private User mUser;
    private boolean mIsFirst;

    public ChangePasswordDialog(@NonNull Context context) {
        super(context);
        mUser = CacheHelper.getInstance().getCurrentUser();
        mIsFirst = mUser.isFirst();
    }

    public void setOnDialogButtonClickListener(OnDialogButtonClickListener listener) {
        mListener = listener;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        requestWindowFeature(Window.FEATURE_NO_TITLE);
        setCanceledOnTouchOutside(false);

        setContentView(R.layout.dialog_change_password);

        ButterKnife.bind(this);

        // Create progress dialog;
        mProgressDialog = new ProgressDialog(getContext());
        mProgressDialog.setIndeterminate(true);
        mProgressDialog.setMessage("Please wait!!!");
        mProgressDialog.setCanceledOnTouchOutside(false);
    }

    @OnClick(R.id.btn_ok)
    void onButtonOkClicked() {
        final String oldPassword = mEditOldPassword.getText().toString();
        final String newPassword = mEditNewPassword.getText().toString();
        if (!TextUtils.isEmpty(oldPassword) && !TextUtils.isEmpty(newPassword)) {
            mProgressDialog.show();
            if (TextUtils.equals(mUser.getPassword(), oldPassword)) {
                mUser.setPassword(newPassword);
                if (mIsFirst)
                    mUser.setFirst(0);

                ApiProvider.getInstance().updateUser(mUser, new OnServerResponseListener<String>() {
                    @Override
                    public void onSuccess(String data) {
                        mProgressDialog.dismiss();
                        if (mIsFirst)
                            CacheHelper.getInstance().saveUser(mUser);
                        dismiss();
                        if (mListener != null) {
                            mListener.onPositiveButtonClicked();
                        }
                    }

                    @Override
                    public void onFail(Throwable t) {
                        mProgressDialog.dismiss();
                        Toast.makeText(getContext(), t.getMessage(), Toast.LENGTH_SHORT).show();
                    }
                });
            } else {
                Toast.makeText(getContext(),
                        getContext().getString(R.string.wrong_old_pass), Toast.LENGTH_SHORT).show();
                mProgressDialog.dismiss();
            }
        } else {
            Toast.makeText(getContext(),
                    getContext().getString(R.string.not_full_info), Toast.LENGTH_SHORT).show();
        }
    }

    @OnClick(R.id.btn_cancel)
    void onButtonCancelClicked() {
        dismiss();
    }

    public interface OnDialogButtonClickListener {
        void onPositiveButtonClicked();
    }
}
