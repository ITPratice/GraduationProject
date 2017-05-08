package self.yue.vehicletracker.data.server;

import android.content.Context;
import android.util.Log;

import com.google.gson.Gson;
import com.google.gson.JsonElement;
import com.google.gson.JsonParser;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import okhttp3.OkHttpClient;
import okhttp3.ResponseBody;
import okhttp3.logging.HttpLoggingInterceptor;
import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;
import retrofit2.Retrofit;
import retrofit2.converter.gson.GsonConverterFactory;
import self.yue.vehicletracker.R;
import self.yue.vehicletracker.data.local.History;
import self.yue.vehicletracker.data.local.Location;
import self.yue.vehicletracker.data.local.ServerHistory;
import self.yue.vehicletracker.data.local.ServerResponse;
import self.yue.vehicletracker.data.local.User;
import self.yue.vehicletracker.data.local.Vehicle;
import self.yue.vehicletracker.util.CacheHelper;
import self.yue.vehicletracker.util.CommonUtil;
import self.yue.vehicletracker.util.interfaces.OnServerResponseListener;

/**
 * Created by dongc on 4/11/2017.
 */

public class ApiProvider {
    private static final String BASE_URL = "http://52.221.199.175:3000/api/";
    private static final int HTTP_OK_CODE = 1;

    private static ApiProvider sInstance;

    private Context mContext;

    private Retrofit mRetrofit;
    private VehicleTrackerService mService;

    private ApiProvider() {
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

    public static ApiProvider getInstance() {
        if (sInstance == null) {
            synchronized (ApiProvider.class) {
                if (sInstance == null)
                    sInstance = new ApiProvider();
            }
        }
        return sInstance;
    }

    public void init(Context context) {
        mContext = context;
    }

    public void login(String email, String password, final OnServerResponseListener<User> listener) {
        mService.login(email, password).enqueue(new Callback<ResponseBody>() {
            @Override
            public void onResponse(Call<ResponseBody> call, Response<ResponseBody> response) {
                if (listener != null) {
                    ResponseBody responseBody = response.body();
                    if (responseBody == null) {
                        listener.onFail(new Throwable("Can\'t login."));
                        return;
                    }

                    try {
                        JsonElement jsonElement = new JsonParser().parse(responseBody.string());
                        User user = new Gson().fromJson(jsonElement, User.class);
                        CacheHelper.getInstance().saveUser(user);
                        listener.onSuccess(user);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            }

            @Override
            public void onFailure(Call<ResponseBody> call, Throwable t) {
                if (!CommonUtil.isNetworkAvailable(mContext) && listener != null) {
                    listener.onFail(new Throwable(mContext.getString(R.string.network_error)));
                }
            }
        });
    }

    public void getCurrentLocation(String licensePlate, final OnServerResponseListener<Location> listener) {
        mService.getCurrentLocation(licensePlate).enqueue(new Callback<Location>() {
            @Override
            public void onResponse(Call<Location> call, Response<Location> response) {
                if (listener != null) {
                    if (response.body() != null) {
                        listener.onSuccess(response.body());
                    } else {
                        listener.onFail(new Throwable("Cannot get current location"));
                    }
                }
            }

            @Override
            public void onFailure(Call<Location> call, Throwable t) {
                if (!CommonUtil.isNetworkAvailable(mContext) && listener != null) {
                    listener.onFail(new Throwable(mContext.getString(R.string.network_error)));
                }
            }
        });
    }

    public void updateUser(User user, final OnServerResponseListener<String> listener) {
        mService.updateProfile(user.getEmail(), user.getUsername(), user.getAddress(),
                user.getPhoneNumber(), user.getPassword(), user.getName(), user.getRole(), 0)
                .enqueue(new Callback<String>() {
                    @Override
                    public void onResponse(Call<String> call, Response<String> response) {
                        if (listener != null) {
                            if (response.body() != null) {
                                if (response.body().equals("" + HTTP_OK_CODE)) {
                                    listener.onSuccess(response.body());
                                } else {
                                    listener.onFail(new Throwable("Cannot update!!!"));
                                }
                            } else {
                                listener.onFail(new Throwable("Cannot update!!!"));
                            }
                        }
                    }

                    @Override
                    public void onFailure(Call<String> call, Throwable t) {
                        if (!CommonUtil.isNetworkAvailable(mContext) && listener != null) {
                            listener.onFail(new Throwable(mContext.getString(R.string.network_error)));
                        }
                    }
                });
    }

    public void getUserByEmail(String email, final OnServerResponseListener<User> listener) {
        mService.getUserByEmail(email).enqueue(new Callback<User>() {
            @Override
            public void onResponse(Call<User> call, Response<User> response) {
                if (listener != null) {
                    if (response.body() != null) {
                        listener.onSuccess(response.body());
                    } else {
                        listener.onFail(new Throwable("No data"));
                    }
                }
            }

            @Override
            public void onFailure(Call<User> call, Throwable t) {
                if (!CommonUtil.isNetworkAvailable(mContext) && listener != null) {
                    listener.onFail(new Throwable(mContext.getString(R.string.network_error)));
                }
            }
        });
    }

    public void getUserVehicles(String email, final OnServerResponseListener<List<Vehicle>> listener) {
        mService.getUserVehicles(email).enqueue(new Callback<ServerResponse<List<Vehicle>>>() {
            @Override
            public void onResponse(Call<ServerResponse<List<Vehicle>>> call, Response<ServerResponse<List<Vehicle>>> response) {
                if (listener != null) {
                    if (response.body() != null) {
                        listener.onSuccess(response.body().data);
                    }
                }
            }

            @Override
            public void onFailure(Call<ServerResponse<List<Vehicle>>> call, Throwable t) {
                if (!CommonUtil.isNetworkAvailable(mContext) && listener != null) {
                    listener.onFail(new Throwable(mContext.getString(R.string.network_error)));
                }
            }
        });
    }

    public void getVehicleHistory(String licensePlate, String date, final OnServerResponseListener<List<History>> listener) {
        mService.getLocationByDate(licensePlate, date)
                .enqueue(new Callback<ServerResponse<List<ServerHistory>>>() {
                    @Override
                    public void onResponse(Call<ServerResponse<List<ServerHistory>>> call, Response<ServerResponse<List<ServerHistory>>> response) {
                        if (listener != null) {
                            if (response.body() != null) {
                                ServerResponse<List<ServerHistory>> serverResponse = response.body();
                                List<ServerHistory> serverHistories = serverResponse.data;
                                List<History> histories = new ArrayList<>();
                                if (serverHistories != null && serverHistories.size() > 0) {
                                    for (ServerHistory serverHistory : serverHistories) {
                                        if (histories.size() == 0) {
                                            History history = new History(serverHistory.date,
                                                    serverHistory.startTime, serverHistory.endTime);
                                            history.locations = new ArrayList<>();
                                            history.locations.add(new Location(serverHistory.latitude, serverHistory.longitude));
                                            histories.add(history);
                                        } else {
                                            History history = histories.get(histories.size() - 1);
                                            if (history.startTime.equals(serverHistory.startTime)) {
                                                history.endTime = serverHistory.endTime;
                                                history.locations.add(new Location(serverHistory.latitude, serverHistory.longitude));
                                            } else {
                                                History tmp = new History(serverHistory.date,
                                                        serverHistory.startTime, serverHistory.endTime);
                                                tmp.locations = new ArrayList<>();
                                                tmp.locations.add(new Location(serverHistory.latitude, serverHistory.longitude));
                                                histories.add(tmp);
                                            }
                                        }
                                    }
                                }
                                listener.onSuccess(histories);
                            } else {
                                listener.onFail(new Throwable("No data"));
                            }
                        }
                    }

                    @Override
                    public void onFailure(Call<ServerResponse<List<ServerHistory>>> call, Throwable t) {
                        if (listener != null && !CommonUtil.isNetworkAvailable(mContext)) {
                            listener.onFail(new Throwable(mContext.getString(R.string.network_error)));
                        }
                    }
                });
    }

    public void updateVehicleState(Vehicle vehicle, final OnServerResponseListener<String> listener) {
        mService.updateVehicleState(vehicle.licensePlate, vehicle.brandId, vehicle.hardwareId,
                vehicle.description, vehicle.typeId, vehicle.email, vehicle.deleted + "",
                vehicle.writeHistory + "")
                .enqueue(new Callback<ResponseBody>() {
                    @Override
                    public void onResponse(Call<ResponseBody> call, Response<ResponseBody> response) {
                        if (listener != null) {
                            if (response.body() != null) {
                                listener.onSuccess("Success");
                            } else {
                                listener.onFail(new Throwable("Can\'t update"));
                            }
                        }
                    }

                    @Override
                    public void onFailure(Call<ResponseBody> call, Throwable t) {
                        if (listener != null && !CommonUtil.isNetworkAvailable(mContext)) {
                            listener.onFail(new Throwable(mContext.getString(R.string.network_error)));
                        }
                    }
                });
    }

    public void getVehicle(final String licensePlate, final OnServerResponseListener<Vehicle> listener) {
        mService.getVehicle(licensePlate).enqueue(new Callback<Vehicle>() {
            @Override
            public void onResponse(Call<Vehicle> call, Response<Vehicle> response) {
                if (listener != null) {
                    if (response.body() != null) {
                        listener.onSuccess(response.body());
                    } else {
                        listener.onFail(new Throwable("Can\'t find vehicle\'s information"));
                    }
                }
            }

            @Override
            public void onFailure(Call<Vehicle> call, Throwable t) {
                if (listener != null && !CommonUtil.isNetworkAvailable(mContext)) {
                    listener.onFail(new Throwable(mContext.getString(R.string.network_error)));
                }
            }
        });
    }
}
