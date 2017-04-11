package self.yue.vehicletracker.data.server;

import java.util.List;

import okhttp3.OkHttpClient;
import okhttp3.logging.HttpLoggingInterceptor;
import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;
import retrofit2.Retrofit;
import retrofit2.converter.gson.GsonConverterFactory;
import self.yue.vehicletracker.data.local.ServerResponse;
import self.yue.vehicletracker.data.local.User;
import self.yue.vehicletracker.util.OnServerResponseListener;

/**
 * Created by dongc on 4/11/2017.
 */

public class ApiProvider {
    private static final String BASE_URL = "http://52.221.199.175:3000/api/";

    private static ApiProvider sInstance;

    private Retrofit mRetrofit;
    private VehicleTrackerService mService;

    public static ApiProvider getInstance() {
        if (sInstance == null) {
            synchronized (ApiProvider.class) {
                if (sInstance == null)
                    sInstance = new ApiProvider();
            }
        }
        return sInstance;
    }

    public void init() {
        HttpLoggingInterceptor interceptor = new HttpLoggingInterceptor();
        interceptor.setLevel(HttpLoggingInterceptor.Level.BODY);
        OkHttpClient client = new OkHttpClient.Builder().addInterceptor(interceptor).build();

        mRetrofit = new Retrofit.Builder()
                .baseUrl(BASE_URL)
                .client(client)
                .addConverterFactory(GsonConverterFactory.create())
                .build();

        mService = mRetrofit.create(VehicleTrackerService.class);
    }

    public void getAllUsers(final OnServerResponseListener<List<User>> listener) {
        mService.getAllUsers().enqueue(new Callback<ServerResponse<List<User>>>() {
            @Override
            public void onResponse(Call<ServerResponse<List<User>>> call, Response<ServerResponse<List<User>>> response) {
                listener.onSuccess(response.body().data);
            }

            @Override
            public void onFailure(Call<ServerResponse<List<User>>> call, Throwable t) {
                listener.onFail(t);
            }
        });
    }
}
