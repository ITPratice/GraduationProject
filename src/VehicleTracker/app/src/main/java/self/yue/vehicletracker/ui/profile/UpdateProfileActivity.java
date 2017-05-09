package self.yue.vehicletracker.ui.profile;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.design.widget.TextInputLayout;
import android.support.v4.content.ContextCompat;
import android.support.v7.widget.Toolbar;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.Toast;

import com.bumptech.glide.Glide;

import butterknife.BindView;
import butterknife.ButterKnife;
import jp.wasabeef.glide.transformations.CropCircleTransformation;
import self.yue.vehicletracker.R;
import self.yue.vehicletracker.base.BaseActivity;
import self.yue.vehicletracker.base.ShowableContent;
import self.yue.vehicletracker.data.local.User;
import self.yue.vehicletracker.data.server.ApiProvider;
import self.yue.vehicletracker.util.CacheHelper;
import self.yue.vehicletracker.util.FontUtil;
import self.yue.vehicletracker.util.interfaces.OnServerResponseListener;

/**
 * Created by dongc on 5/8/2017.
 */

public class UpdateProfileActivity extends BaseActivity implements ShowableContent {
    @BindView(R.id.input_layout_name)
    TextInputLayout mInputLayoutName;
    @BindView(R.id.input_layout_address)
    TextInputLayout mInputLayoutAddress;
    @BindView(R.id.input_layout_phone)
    TextInputLayout mInputLayoutPhone;
    @BindView(R.id.edit_name)
    EditText mEditName;
    @BindView(R.id.edit_address)
    EditText mEditAddress;
    @BindView(R.id.edit_phone)
    EditText mEditPhone;
    @BindView(R.id.btn_update)
    Button mButtonUpdate;
    @BindView(R.id.toolbar)
    Toolbar mToolbar;
    @BindView(R.id.img_avatar)
    ImageView mImageAvatar;

    private User mUser;

    @Override
    protected int getLayoutResId() {
        return R.layout.activity_update_profile;
    }

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        ButterKnife.bind(this);

        mUser = CacheHelper.getInstance().getCurrentUser();

        initViews();

        setSupportActionBar(mToolbar);
        getSupportActionBar().setDisplayShowTitleEnabled(false);
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);
        getSupportActionBar().setHomeAsUpIndicator(R.drawable.ic_close);
        mToolbar.setTitle("Profile");
        mToolbar.setTitleTextColor(ContextCompat.getColor(this, R.color.white));
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        if (item.getItemId() == android.R.id.home) {
            onBackPressed();
        }
        return super.onOptionsItemSelected(item);
    }

    @Override
    public void showToast(String message) {
        Toast.makeText(this, message, Toast.LENGTH_SHORT).show();
    }

    private void initViews() {
        mEditName.setText(mUser.getName());
        mEditAddress.setText(mUser.getAddress());
        mEditPhone.setText(mUser.getPhoneNumber());
        Glide.with(this).fromResource().load(R.drawable.img_default_avatar)
                .bitmapTransform(new CropCircleTransformation(this)).into(mImageAvatar);

        mButtonUpdate.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mUser.setName(mEditName.getText().toString());
                mUser.setAddress(mEditAddress.getText().toString());
                mUser.setPhoneNumber(mEditPhone.getText().toString());

                ApiProvider.getInstance().updateUser(mUser, new OnServerResponseListener<String>() {
                    @Override
                    public void onSuccess(String data) {
                        CacheHelper.getInstance().saveUser(mUser);
                        showToast("Update successfully!");
                    }

                    @Override
                    public void onFail(Throwable t) {
                        showToast(t.getMessage());
                    }
                });
            }
        });

        setFont();
    }

    private void setFont() {
        mButtonUpdate.setTypeface(FontUtil.getInstance().getCustomFont(this, "fonts/iCiel_Alina.otf"));
    }
}
