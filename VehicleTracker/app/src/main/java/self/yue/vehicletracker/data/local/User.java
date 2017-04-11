package self.yue.vehicletracker.data.local;

import com.google.gson.annotations.SerializedName;

/**
 * Created by dongc on 4/11/2017.
 */

public class User {
    @SerializedName("Id")
    private String mId;
    @SerializedName("Email")
    private String mEmail;
    @SerializedName("Address")
    private String mAddress;
    @SerializedName("NumberPlate")
    private String mNumberPlate;
    @SerializedName("PhoneNumber")
    private String mPhoneNumber;

    public String getId() {
        return mId;
    }

    public void setId(String id) {
        mId = id;
    }

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
}
