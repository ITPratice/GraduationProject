package self.yue.vehicletracker.ui.login;

import android.app.ProgressDialog;
import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.text.TextUtils;
import android.view.KeyEvent;
import android.view.View;
import android.view.inputmethod.EditorInfo;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import self.yue.vehicletracker.R;
import self.yue.vehicletracker.base.BaseActivity;
import self.yue.vehicletracker.base.BaseActivityBehaviour;
import self.yue.vehicletracker.base.ShowableContent;
import self.yue.vehicletracker.data.local.User;
import self.yue.vehicletracker.data.server.ApiProvider;
import self.yue.vehicletracker.ui.main.MainActivity;
import self.yue.vehicletracker.ui.widgets.ChangePasswordDialog;
import self.yue.vehicletracker.util.CacheHelper;
import self.yue.vehicletracker.util.FontUtil;
import self.yue.vehicletracker.util.interfaces.OnServerResponseListener;

/**
 * Created by dongc on 3/18/2017.
 */

public class LoginActivity extends BaseActivity implements ShowableContent, BaseActivityBehaviour {
    private EditText mEditEmail;
    private EditText mEditPassword;
    private Button mButtonLogin;

    private ProgressDialog mProgressDialog;

    @Override
    protected int getLayoutResId() {
        return R.layout.activity_login;
    }

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        initViews();

        User user = CacheHelper.getInstance().getCurrentUser();
        if (user != null) {
            mEditEmail.setText(user.getEmail());
            mEditPassword.setText(user.getPassword());
        }

        mProgressDialog = new ProgressDialog(this);
        mProgressDialog.setIndeterminate(true);
        mProgressDialog.setMessage(getString(R.string.please_wait));
        mProgressDialog.setCanceledOnTouchOutside(false);
    }

    @Override
    public void showToast(String message) {
        Toast.makeText(this, message, Toast.LENGTH_SHORT).show();
    }

    @Override
    public Intent newIntent() {
        return new Intent(this, MainActivity.class);
    }

    @Override
    public Intent newIntent(Bundle data) {
        return null;
    }

    private void initViews() {
        mEditEmail = (EditText) findViewById(R.id.et_id);
        mEditPassword = (EditText) findViewById(R.id.et_password);

        mButtonLogin = (Button) findViewById(R.id.btn_login);

        mButtonLogin.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                login();
            }
        });

        mEditPassword.setOnEditorActionListener(new TextView.OnEditorActionListener() {
            @Override
            public boolean onEditorAction(TextView v, int actionId, KeyEvent event) {
                if (actionId == EditorInfo.IME_ACTION_DONE)
                    login();
                return false;
            }
        });

        setFont();
    }

    private void login() {
        final String email = mEditEmail.getText().toString();
        String password = mEditPassword.getText().toString();
        if (TextUtils.isEmpty(email)) {
            showToast(getString(R.string.empty_id));
        } else if (TextUtils.isEmpty(password)) {
            showToast(getString(R.string.empty_password));
        } else {
            mProgressDialog.show();
            ApiProvider.getInstance().login(email, password, new OnServerResponseListener<User>() {
                @Override
                public void onSuccess(User data) {
                    mProgressDialog.dismiss();
                    if (data.isFirst()) {
                        ChangePasswordDialog dialog = new ChangePasswordDialog(LoginActivity.this);
                        dialog.setOnDialogButtonClickListener(new ChangePasswordDialog.OnDialogButtonClickListener() {
                            @Override
                            public void onPositiveButtonClicked() {
                                startActivity(new Intent(LoginActivity.this, MainActivity.class));
                                finish();
                            }
                        });
                        dialog.show();
                    } else {
                        CacheHelper.getInstance().saveUser(data);
                        startActivity(new Intent(LoginActivity.this, MainActivity.class));
                        finish();
                    }
                }

                @Override
                public void onFail(Throwable t) {
                    mProgressDialog.dismiss();
                    showToast(t.getMessage());
                }
            });
        }
    }

    private void setFont() {
        mEditEmail.setTypeface(FontUtil.getInstance().getMainLightFont());
        mEditPassword.setTypeface(FontUtil.getInstance().getMainLightFont());
        mButtonLogin.setTypeface(FontUtil.getInstance().getCustomFont(this, "fonts/iCiel_Alina.otf"));
    }
}
