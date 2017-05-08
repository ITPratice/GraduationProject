package self.yue.vehicletracker.data.local;

import android.os.Parcel;
import android.os.Parcelable;

import com.google.gson.annotations.SerializedName;

/**
 * Created by dongc on 5/5/2017.
 */

public class Location implements Parcelable {
    @SerializedName("Date")
    public String date;
    @SerializedName("StartTime")
    public String startTime;
    @SerializedName("EndTime")
    public String endTime;
    @SerializedName("Latitude")
    public String latitude;
    @SerializedName("Longitude")
    public String longitude;
    @SerializedName("NumberPlate")
    public String numberPlate;

    public Location() {
    }

    public Location(String latitude, String longitude) {
        this.latitude = latitude;
        this.longitude = longitude;
    }

    protected Location(Parcel in) {
        date = in.readString();
        startTime = in.readString();
        endTime = in.readString();
        latitude = in.readString();
        longitude = in.readString();
        numberPlate = in.readString();
    }

    public static final Creator<Location> CREATOR = new Creator<Location>() {
        @Override
        public Location createFromParcel(Parcel in) {
            return new Location(in);
        }

        @Override
        public Location[] newArray(int size) {
            return new Location[size];
        }
    };

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeString(date);
        dest.writeString(startTime);
        dest.writeString(endTime);
        dest.writeString(latitude);
        dest.writeString(longitude);
        dest.writeString(numberPlate);
    }
}
