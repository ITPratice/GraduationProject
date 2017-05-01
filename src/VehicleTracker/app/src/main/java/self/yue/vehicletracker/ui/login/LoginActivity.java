package self.yue.vehicletracker.ui.login;

import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.design.widget.Snackbar;
import android.text.TextUtils;
import android.view.KeyEvent;
import android.view.View;
import android.view.inputmethod.EditorInfo;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import self.yue.vehicletracker.R;
import self.yue.vehicletracker.base.BaseActivity;
import self.yue.vehicletracker.base.BaseActivityBehaviour;
import self.yue.vehicletracker.base.ShowableContent;
import self.yue.vehicletracker.data.server.ApiProvider;
import self.yue.vehicletracker.ui.main.MainActivity;

/**
 * Created by dongc on 3/18/2017.
 */

public class LoginActivity extends BaseActivity implements ShowableContent, BaseActivityBehaviour {
    private EditText mEditId;
    private EditText mEditPassword;
    private View mContainer;

    @Override
    protected int getLayoutResId() {
        return R.layout.activity_login;
    }

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        initViews();
        ApiProvider.getInstance().init();
    }

    @Override
    public void showToast(String message) {
        Toast.makeText(this, message, Toast.LENGTH_SHORT).show();
    }

    @Override
    public void showSnackbar(String message) {
        Snackbar.make(mContainer, message, Snackbar.LENGTH_SHORT).show();
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
        mEditId = (EditText) findViewById(R.id.et_id);
        mEditPassword = (EditText) findViewById(R.id.et_password);
        mContainer = findViewById(R.id.container);

        findViewById(R.id.btn_login).setOnClickListener(new View.OnClickListener() {
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
    }

    private void login() {
        String email = mEditId.getText().toString();
        String password = mEditPassword.getText().toString();
        if (TextUtils.isEmpty(email)) {
            showSnackbar(getString(R.string.empty_id));
        } else if (TextUtils.isEmpty(password)) {
            showSnackbar(getString(R.string.empty_password));
        } else {
            startActivity(newIntent());
//            ApiProvider.getInstance().login(email, password, new OnServerResponseListener<String>() {
//                @Override
//                public void onSuccess(String data) {
//                    if (data.equals("OK")) {
//                        startActivity(newIntent());
//                    } else {
//                        Toast.makeText(LoginActivity.this, "Fail", Toast.LENGTH_SHORT).show();
//                    }
//                }
//
//                @Override
//                public void onFail(Throwable t) {
//                    Toast.makeText(LoginActivity.this, t.getMessage(), Toast.LENGTH_SHORT).show();
//                }
//            });
        }
    }
}
