package self.yue.vehicletracker.data.local;

import java.util.Calendar;
import java.util.Locale;

/**
 * Created by dongc on 4/10/2017.
 */

public class DateTime {
    private int mDay;
    private int mMonth;
    private int mYear;

    private int mHour;
    private int mMinute;
    private int mSecond;

    public DateTime() {
    }

    public DateTime(int day, int month, int year) {
        mDay = day;
        mMonth = month;
        mYear = year;
    }

    public DateTime(int day, int month, int year, int hour, int minute, int second) {
        mDay = day;
        mMonth = month;
        mYear = year;
        mHour = hour;
        mMinute = minute;
        mSecond = second;
    }

    public int getDay() {
        return mDay;
    }

    public void setDay(int day) {
        mDay = day;
    }

    public int getMonth() {
        return mMonth;
    }

    public void setMonth(int month) {
        mMonth = month;
    }

    public int getYear() {
        return mYear;
    }

    public void setYear(int year) {
        mYear = year;
    }

    public int getHour() {
        return mHour;
    }

    public void setHour(int hour) {
        mHour = hour;
    }

    public int getMinute() {
        return mMinute;
    }

    public void setMinute(int minute) {
        mMinute = minute;
    }

    public int getSecond() {
        return mSecond;
    }

    public void setSecond(int second) {
        mSecond = second;
    }

    public static DateTime getNow() {
        Calendar calendar = Calendar.getInstance();
        DateTime dateTime = new DateTime();
        dateTime.setDay(calendar.get(Calendar.DAY_OF_MONTH));
        dateTime.setMonth(calendar.get(Calendar.MONTH));
        dateTime.setYear(calendar.get(Calendar.YEAR));
        dateTime.setHour(calendar.get(Calendar.HOUR_OF_DAY));
        dateTime.setMinute(calendar.get(Calendar.MINUTE));
        dateTime.setSecond(calendar.get(Calendar.SECOND));
        return dateTime;
    }

    public int compareToByDate(DateTime dateTime) {
        if (mDay == dateTime.getDay() && mMonth == dateTime.getMonth() && mYear == dateTime.getYear())
            return 0;
        return -1;
    }

    public long toMillis() {
        Calendar calendar = Calendar.getInstance();
        calendar.set(Calendar.DAY_OF_MONTH, mDay);
        calendar.set(Calendar.MONTH, mMonth);
        calendar.set(Calendar.YEAR, mYear);
        calendar.set(Calendar.HOUR_OF_DAY, mHour);
        calendar.set(Calendar.MINUTE, mMinute);
        calendar.set(Calendar.SECOND, mSecond);
        return calendar.getTimeInMillis();
    }

    public String toShortDateString() {
        String day = mDay < 10 ? "0" + mDay : "" + mDay;
        String month = mMonth < 10 ? "0" + mMonth : "" + mMonth;
        return day + "/" + month + "/" + mYear;
    }

    public String toShortTimeString() {
        String hour = mHour < 10 ? "0" + mHour : "" + mHour;
        String minute = mMinute < 10 ? "0" + mMinute : "" + mMinute;
        return hour + ":" + minute;
    }

    public String toDayOfWeekString() {
        Calendar calendar = Calendar.getInstance();
        calendar.set(Calendar.DAY_OF_MONTH, mDay);
        calendar.set(Calendar.MONTH, mMonth);
        calendar.set(Calendar.YEAR, mYear);
        return calendar.getDisplayName(Calendar.DAY_OF_WEEK, Calendar.SHORT, Locale.getDefault());
    }

    public String displayNameOfMonth() {
        Calendar calendar = Calendar.getInstance();
        calendar.set(Calendar.MONTH, mMonth);
        return calendar.getDisplayName(Calendar.MONTH, Calendar.SHORT, Locale.getDefault());
    }

    public String toSuitestDateTimeString() {
        DateTime now = getNow();
        if (mDay == now.getDay())
            return "AT " + toShortTimeString();
        return "";
    }
}
