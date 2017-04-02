package self.yue.vehicletracker.base;

import android.content.Intent;
import android.os.Bundle;

/**
 * Created by dongc on 3/18/2017.
 */

public interface BaseActivityBehaviour {
    Intent newIntent();

    Intent newIntent(Bundle data);
}
