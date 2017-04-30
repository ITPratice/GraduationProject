package self.yue.vehicletracker.util;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.drawable.Drawable;
import android.support.v4.content.ContextCompat;

import com.google.android.gms.maps.model.BitmapDescriptor;
import com.google.android.gms.maps.model.BitmapDescriptorFactory;

/**
 * Created by dongc on 4/20/2017.
 */

public class BitmapHelper {
    public static BitmapDescriptor getBitmapDescriptor(Context context, int id) {
        Drawable vectorDrawable = ContextCompat.getDrawable(context, id);
        int w = vectorDrawable.getIntrinsicWidth();
        int h = vectorDrawable.getIntrinsicHeight();
        vectorDrawable.setBounds(0, 0, w, h);
        Bitmap bm = Bitmap.createBitmap(w, h, Bitmap.Config.ARGB_8888);
        Canvas canvas = new Canvas(bm);
        vectorDrawable.draw(canvas);
        return BitmapDescriptorFactory.fromBitmap(bm);
    }
}
