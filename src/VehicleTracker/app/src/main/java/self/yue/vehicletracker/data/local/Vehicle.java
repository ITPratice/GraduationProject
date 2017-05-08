package self.yue.vehicletracker.data.local;

import com.google.gson.annotations.SerializedName;

/**
 * Created by dongc on 5/5/2017.
 */

public class Vehicle {
    @SerializedName("UserEmail")
    public String email;
    @SerializedName("NumberPlate")
    public String licensePlate;
    @SerializedName("BranchId")
    public String brandId;
    @SerializedName("TypeId")
    public String typeId;
    @SerializedName("HardwareId")
    public String hardwareId;
    @SerializedName("Description")
    public String description;
    @SerializedName("Deleted")
    public int deleted;
    @SerializedName("WriteHistory")
    public int writeHistory;
}
