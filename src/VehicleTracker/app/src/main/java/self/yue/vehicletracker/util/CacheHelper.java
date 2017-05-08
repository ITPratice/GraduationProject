package self.yue.vehicletracker.util;

import android.content.Context;
import android.content.SharedPreferences;
import android.text.TextUtils;

import com.google.gson.Gson;

import self.yue.vehicletracker.data.local.User;

/**
 * Created by dongc on 4/16/2017.
 */

public class CacheHelper {
    private static final String SHARED_PREF_NAME = CacheHelper.class.getPackage().getName();
    private static final String PREF_USER = "user";
    private static final String PREF_EMAIL = "email";
    private static final String PREF_PASSWORD = "password";
    private static final String PREF_TOKEN = "token";
    private static CacheHelper sInstance;
    private SharedPreferences mSharedPreferences;
    private SharedPreferences.Editor mPrefEditor;
    private Gson mGson;

    private CacheHelper() {

    }

    public static CacheHelper getInstance() {
        if (sInstance == null) {
            synchronized (CacheHelper.class) {
                if (sInstance == null) {
                    sInstance = new CacheHelper();
                }
            }
        }
        return sInstance;
    }

    public void init(Context context) {
        mSharedPreferences = context.getSharedPreferences(SHARED_PREF_NAME, Context.MODE_PRIVATE);
        mGson = new Gson();
    }

    public User getCurrentUser() {
        if (mSharedPreferences.contains(PREF_USER)) {
            String data = mSharedPreferences.getString(PREF_USER, "");
            if (!TextUtils.isEmpty(data)) {
                return mGson.fromJson(data, User.class);
            }
        }
        return null;
    }

    public void saveUser(User user) {
        mPrefEditor = mSharedPreferences.edit();
        mPrefEditor.putString(PREF_USER, mGson.toJson(user));
        mPrefEditor.apply();
    }

    public void saveAccount(String email, String password) {
        mPrefEditor = mSharedPreferences.edit();
        mPrefEditor.putString(PREF_EMAIL, email);
        mPrefEditor.putString(PREF_PASSWORD, password);
        mPrefEditor.apply();
    }

    public void removeCurrentUser() {
        mPrefEditor = mSharedPreferences.edit();
        mPrefEditor.remove(PREF_USER);
        mPrefEditor.apply();
    }

    public void saveToken(String token) {
        mPrefEditor = mSharedPreferences.edit();
        mPrefEditor.putString(PREF_TOKEN, token);
        mPrefEditor.apply();
    }

    public String getToken() {
        if (mSharedPreferences.contains(PREF_TOKEN))
            return mSharedPreferences.getString(PREF_TOKEN, "");
        return "";
    }

    public String getEmail() {
        return mSharedPreferences.getString(PREF_EMAIL, "");
    }

    public String getPassword() {
        return mSharedPreferences.getString(PREF_PASSWORD, "");
    }
}
