package self.yue.vehicletracker.data.local;

import com.google.gson.annotations.SerializedName;

/**
 * Created by dongc on 4/11/2017.
 */

public class User {
    @SerializedName("Email")
    private String mEmail;
    @SerializedName("Address")
    private String mAddress;
    @SerializedName("NumberPlate")
    private String mNumberPlate;
    @SerializedName("PhoneNumber")
    private String mPhoneNumber;
    @SerializedName("Fullname")
    private String mName;
    @SerializedName("Password")
    private String mPassword;
    @SerializedName("Username")
    private String mUsername;
    @SerializedName("Role")
    private int mRole;
    @SerializedName("First")
    private int mIsFirst;

    public String getEmail() {
        return mEmail;
    }

    public void setEmail(String email) {
        mEmail = email;
    }

    public String getAddress() {
        return mAddress;
    }

    public void setAddress(String address) {
        mAddress = address;
    }

    public String getNumberPlate() {
        return mNumberPlate;
    }

    public void setNumberPlate(String numberPlate) {
        mNumberPlate = numberPlate;
    }

    public String getPhoneNumber() {
        return mPhoneNumber;
    }

    public void setPhoneNumber(String phoneNumber) {
        mPhoneNumber = phoneNumber;
    }

    public String getName() {
        return mName;
    }

    public void setName(String name) {
        mName = name;
    }

    public String getPassword() {
        return mPassword;
    }

    public void setPassword(String password) {
        mPassword = password;
    }

    public String getUsername() {
        return mUsername;
    }

    public void setUsername(String username) {
        mUsername = username;
    }

    public int getRole() {
        return mRole;
    }

    public void setRole(int role) {
        mRole = role;
    }

    public boolean isFirst() {
        return mIsFirst == 1;
    }

    public void setFirst(int first) {
        mIsFirst = first;
    }
}
