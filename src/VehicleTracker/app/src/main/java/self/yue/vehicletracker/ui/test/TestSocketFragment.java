package self.yue.vehicletracker.ui.test;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.widget.EditText;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;

import self.yue.vehicletracker.R;
import self.yue.vehicletracker.base.BaseFragment;

/**
 * Created by dongc on 3/19/2017.
 */

public class TestSocketFragment extends BaseFragment {
    public static final String SERVER_ADDRESS = "54.179.174.237";
    public static final int SERVER_PORT = 3000;

    private EditText mEditData;

    private Socket mSocket;
    private BufferedReader in;

    @Override
    protected int getLayoutResId() {
        return R.layout.fragment_test_socket;
    }

    @Override
    public void onViewCreated(View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        initViews(view);
    }

    private void initViews(View view) {
        mEditData = (EditText) view.findViewById(R.id.et_data);

        view.findViewById(R.id.btn_connect).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new Thread(new ClientThread()).start();
            }
        });

        view.findViewById(R.id.btn_disconnect).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

            }
        });

        view.findViewById(R.id.btn_send).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    String data = mEditData.getText().toString();
                    Log.e("Dafuq", data);
                    PrintWriter out = new PrintWriter(mSocket.getOutputStream(), true);
                    out.println(data);
//                    String fuck = in.readLine();
//                    if (!TextUtils.isEmpty(fuck))
//                        Log.e("Dau phong", fuck);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });
    }

    class ClientThread implements Runnable {

        @Override
        public void run() {
            try {
                InetAddress serverAddress = InetAddress.getByName(SERVER_ADDRESS);
                mSocket = new Socket(SERVER_ADDRESS, SERVER_PORT);
                in = new BufferedReader(new InputStreamReader(mSocket.getInputStream()));
            } catch (UnknownHostException e1) {
                e1.printStackTrace();
            } catch (IOException e1) {
                e1.printStackTrace();
            }

        }
    }
}
