package self.yue.vehicletracker.data.local;

import android.os.Parcel;
import android.os.Parcelable;

import java.util.List;

/**
 * Created by dongc on 5/7/2017.
 */

public class History implements Parcelable {
    public String date;
    public String startTime;
    public String endTime;
    public List<Location> locations;

    public History() {
    }

    public History(String date, String startTime, String endTime) {
        this.date = date;
        this.startTime = startTime;
        this.endTime = endTime;
    }

    protected History(Parcel in) {
        date = in.readString();
        startTime = in.readString();
        endTime = in.readString();
        locations = in.createTypedArrayList(Location.CREATOR);
    }

    public static final Creator<History> CREATOR = new Creator<History>() {
        @Override
        public History createFromParcel(Parcel in) {
            return new History(in);
        }

        @Override
        public History[] newArray(int size) {
            return new History[size];
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
        dest.writeTypedList(locations);
    }
}
