package self.yue.vehicletracker.ui.main.history;

import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import java.util.List;

import self.yue.vehicletracker.R;
import self.yue.vehicletracker.data.local.History;
import self.yue.vehicletracker.data.local.ServerHistory;
import self.yue.vehicletracker.util.interfaces.OnRecyclerItemInteractListener;

/**
 * Created by dongc on 5/2/2017.
 */

public class HistoryAdapter extends RecyclerView.Adapter<HistoryAdapter.ItemHolder> {
    private List<History> mHistories;

    private OnRecyclerItemInteractListener mListener;

    public HistoryAdapter(List<History> histories) {
        mHistories = histories;
    }

    public void setListener(OnRecyclerItemInteractListener listener) {
        mListener = listener;
    }

    @Override
    public ItemHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        return new ItemHolder(LayoutInflater.from(parent.getContext())
                .inflate(R.layout.item_history, parent, false));
    }

    @Override
    public void onBindViewHolder(ItemHolder holder, int position) {
        History serverHistory = mHistories.get(position);

//        holder.textStartLocation.setText(TextUtils.isEmpty(serverHistory.stat));

        holder.textStartTime.setText(serverHistory.startTime);
        holder.textEndTime.setText(serverHistory.endTime);

        holder.itemContainer.setTag(position);
        holder.itemContainer.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (mListener != null) {
                    mListener.onRecyclerItemClick((int) v.getTag());
                }
            }
        });
    }

    @Override
    public int getItemCount() {
        return mHistories != null ? mHistories.size() : 0;
    }

    static class ItemHolder extends RecyclerView.ViewHolder {
        public View itemContainer;
        public TextView textStartTime;
        public TextView textEndTime;
        public TextView textStartLocation;
        public TextView textEndLocation;

        public ItemHolder(View itemView) {
            super(itemView);
            itemContainer = itemView.findViewById(R.id.item_container);
            textStartTime = (TextView) itemView.findViewById(R.id.text_start_time);
            textEndTime = (TextView) itemView.findViewById(R.id.text_end_time);
            textStartLocation = (TextView) itemView.findViewById(R.id.text_start_location);
            textEndLocation = (TextView) itemView.findViewById(R.id.text_end_location);
        }
    }
}
