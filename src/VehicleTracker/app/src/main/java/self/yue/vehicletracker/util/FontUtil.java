package self.yue.vehicletracker.util;

import android.content.Context;
import android.graphics.Typeface;

/**
 * Created by dongc on 4/3/2017.
 */

public class FontUtil {

    private static FontUtil sInstance;
    private Typeface mMainLightFont;
    private Typeface mMainBoldFont;
    private Typeface mMainSemiboldFont;
    private Typeface mMainRegularFont;

    private FontUtil() {
    }

    public static FontUtil getInstance() {
        if (sInstance == null) {
            synchronized (FontUtil.class) {
                if (sInstance == null)
                    sInstance = new FontUtil();
            }
        }
        return sInstance;
    }

    public void init(Context context) {
        mMainLightFont = Typeface.createFromAsset(context.getAssets(), "fonts/SanFrancisco-Light.otf");
        mMainBoldFont = Typeface.createFromAsset(context.getAssets(), "fonts/SanFrancisco-Bold.otf");
        mMainSemiboldFont = Typeface.createFromAsset(context.getAssets(), "fonts/SanFrancisco-Semibold.otf");
        mMainRegularFont = Typeface.createFromAsset(context.getAssets(), "fonts/SanFrancisco-Regular.otf");
    }

    public Typeface getMainLightFont() {
        return mMainLightFont;
    }

    public Typeface getMainBoldFont() {
        return mMainBoldFont;
    }

    public Typeface getMainSemiboldFont() {
        return mMainSemiboldFont;
    }

    public Typeface getMainRegularFont() {
        return mMainRegularFont;
    }

    public Typeface getCustomFont(Context context, String fontPath) {
        return Typeface.createFromAsset(context.getAssets(), fontPath);
    }
}
