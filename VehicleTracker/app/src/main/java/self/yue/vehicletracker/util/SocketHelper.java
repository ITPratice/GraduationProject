package self.yue.vehicletracker.util;

import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;

/**
 * Created by dongc on 4/2/2017.
 */

public class SocketHelper {
    private static final String IP_ADDRESS = "54.179.174.237";
    private static final int SERVER_PORT = 3000;

    private Socket mSocket;
    private static SocketHelper sInstance;

    private SocketHelper() {

    }

    public static SocketHelper getInstance() {
        if (sInstance == null) {
            synchronized (SocketHelper.class) {
                if (sInstance == null) {
                    sInstance = new SocketHelper();
                }
            }
        }
        return sInstance;
    }

    public void sendData(String data) throws IOException {
        if (!mSocket.isClosed() && mSocket.isBound()) {
            PrintWriter out = new PrintWriter(
                    new BufferedWriter(new OutputStreamWriter(mSocket.getOutputStream())), true);
            out.println(data);
        }
    }
}
