package self.yue.vehicletracker.data.server;

import okhttp3.OkHttpClient;
import okhttp3.logging.HttpLoggingInterceptor;
import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;
import retrofit2.Retrofit;
import retrofit2.converter.gson.GsonConverterFactory;
import self.yue.vehicletracker.data.local.google.GoogleServerResponse;
import self.yue.vehicletracker.data.local.google.Route;
import self.yue.vehicletracker.util.interfaces.OnServerResponseListener;

/**
 * Created by dongc on 4/20/2017.
 */

public class GoogleApiProvider {
    private static final String BASE_URL = "https://maps.googleapis.com/maps/api/";

    private static GoogleApiProvider sInstance;

    private Retrofit mRetrofit;
    private GoogleService mService;

    public static GoogleApiProvider getInstance() {
        if (sInstance == null) {
            synchronized (ApiProvider.class) {
                if (sInstance == null)
                    sInstance = new GoogleApiProvider();
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

        mService = mRetrofit.create(GoogleService.class);
    }

    public void getDirection(String origin, String destination, String key, final OnServerResponseListener<Route> listener) {
        mService.getDirection(origin, destination, key).enqueue(new Callback<GoogleServerResponse>() {
            @Override
            public void onResponse(Call<GoogleServerResponse> call, Response<GoogleServerResponse> response) {
                if (response != null && listener != null) {
                    GoogleServerResponse serverResponse = response.body();
                    if (serverResponse != null && serverResponse.status.equals("OK")) {
                        listener.onSuccess(serverResponse.routes.get(0));
                    }
                }
            }

            @Override
            public void onFailure(Call<GoogleServerResponse> call, Throwable t) {

            }
        });
    }
}
