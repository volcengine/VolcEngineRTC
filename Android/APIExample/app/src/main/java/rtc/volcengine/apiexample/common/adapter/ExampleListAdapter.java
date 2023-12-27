package rtc.volcengine.apiexample.common.adapter;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.RelativeLayout;
import android.widget.TextView;

import androidx.recyclerview.widget.RecyclerView;

import java.util.ArrayList;
import java.util.List;

import rtc.volcengine.apiexample.R;
import rtc.volcengine.apiexample.common.data.ExampleInfo;

public class ExampleListAdapter extends RecyclerView.Adapter{

    private List<ExampleInfo> exampleList = new ArrayList<>();
    private OnItemClickListener mOnItemClickListener;

    @Override
    public RecyclerView.ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View v = LayoutInflater.from(parent.getContext()).inflate(R.layout.layout_api_list_item, parent, false);
        return new MyViewHolder(v);
    }

    @Override
    public void onBindViewHolder(final RecyclerView.ViewHolder holder, int position) {
        final MyViewHolder myViewHolder = (MyViewHolder) holder;
        if (mOnItemClickListener != null) {
        }
        ExampleInfo exampleInfo = exampleList.get(position);
        if (exampleInfo.getCategory() != null) {
            myViewHolder.categoryRV.setVisibility(View.VISIBLE);
            myViewHolder.categoryName.setText(exampleInfo.getCategory());
        } else {
            myViewHolder.categoryRV.setVisibility(View.GONE);
        }
        myViewHolder.list.setOnClickListener(v -> {
            if (mOnItemClickListener != null) {
                int pos = myViewHolder.getLayoutPosition();
                mOnItemClickListener.onItemClick(v, pos);
            }
        });

        myViewHolder.apiName.setText(exampleInfo.getExampleName());
    }

    @Override
    public int getItemCount() {
        return exampleList.size();
    }


    public void addApiInfo(ExampleInfo exampleInfo) {
        exampleList.add(exampleInfo);
        notifyDataSetChanged();
    }

    public void setExampleList(List<ExampleInfo> list) {
        exampleList = list;
        notifyDataSetChanged();
    }

    public void clear() {
        exampleList.clear();
    }

    public static class MyViewHolder extends RecyclerView.ViewHolder {
        RelativeLayout list;
        TextView apiName;
        TextView categoryName;
        RelativeLayout categoryRV;

        MyViewHolder(View itemView) {
            super(itemView);
            list = itemView.findViewById(R.id.list);
            apiName = itemView.findViewById(R.id.api_name);
            categoryName = itemView.findViewById(R.id.category_name);
            categoryRV = itemView.findViewById(R.id.category);
        }
    }

    public void setOnItemClickListener(OnItemClickListener mOnItemClickListener) {
        this.mOnItemClickListener = mOnItemClickListener;
    }

    public interface OnItemClickListener {
        void onItemClick(View view, int position);
    }
}
