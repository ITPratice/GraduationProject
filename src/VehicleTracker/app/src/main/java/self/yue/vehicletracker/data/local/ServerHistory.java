package self.yue.vehicletracker.data.local;

import android.os.Parcel;
import android.os.Parcelable;

import com.google.gson.annotations.SerializedName;

/**
 * Created by dongc on 5/2/2017.
 */

public class ServerHistory implements Parcelable {
    @SerializedName("StartTime")
    public String startTime;
    @SerializedName("EndTime")
    public String endTime;
    @SerializedName("Date")
    public String date;
    @SerializedName("Latitude")
    public String latitude;
    @SerializedName("Longitude")
    public String longitude;

    public ServerHistory() {
    }

    public ServerHistory(String startTime, String endTime) {
        this.startTime = startTime;
        this.endTime = endTime;
    }

    protected ServerHistory(Parcel in) {
        startTime = in.readString();
        endTime = in.readString();
        date = in.readString();
        latitude = in.readString();
        longitude = in.readString();
    }

    public static final Creator<ServerHistory> CREATOR = new Creator<ServerHistory>() {
        @Override
        public ServerHistory createFromParcel(Parcel in) {
            return new ServerHistory(in);
        }

        @Override
        public ServerHistory[] newArray(int size) {
            return new ServerHistory[size];
        }
    };

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeString(startTime);
        dest.writeString(endTime);
        dest.writeString(date);
        dest.writeString(latitude);
        dest.writeString(longitude);
    }
}
