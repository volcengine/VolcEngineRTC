package com.faceunity.nama.base;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;


import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.recyclerview.widget.RecyclerView;

import com.faceunity.nama.listener.OnMultiClickListener;


import java.util.ArrayList;
import java.util.HashMap;

/**
 * DESC：RecycleView 通用适配器
 * Created on 2021/4/26
 */
public class BaseListAdapter<T> extends RecyclerView.Adapter<BaseViewHolder> {
    private ArrayList<T> data;
    private BaseDelegate<T> viewHolderDelegate;
    private int[] mLayouts;
    private HashMap<Integer, BaseViewHolder> mViewHolder = new HashMap<>();

    public BaseListAdapter(ArrayList<T> data, BaseDelegate<T> viewHolderDelegate, int... resLayouts) {
        mLayouts = resLayouts;
        this.data = data;
        this.viewHolderDelegate = viewHolderDelegate;
    }


    @NonNull
    @Override
    public BaseViewHolder onCreateViewHolder(@NonNull ViewGroup viewGroup, int viewType) {
        View view = LayoutInflater.from(viewGroup.getContext()).inflate(getLayoutId(viewType), viewGroup, false);
        return new BaseViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull BaseViewHolder holder, int position) {
        mViewHolder.put(position, holder);
        viewHolderDelegate.convert(getItemViewType(position), holder, data.get(position), position);
        bindViewClickListener(holder, position);
    }

    @Override
    public int getItemCount() {
        return data.size();
    }


    public void setData(ArrayList<T> items) {
        data.clear();
        data.addAll(items);
        notifyDataSetChanged();
    }

    public T getData(int position) {
        return data.get(position);
    }


    public BaseViewHolder getViewHolderByPosition(int position) {
        if (!mViewHolder.containsKey(position)) {
            return null;
        }
        return mViewHolder.get(position);
    }

    public View getViewByPosition(int position) {
        if (mViewHolder.get(position) == null) {
            return null;
        }
        return mViewHolder.get(position).itemView;
    }


    private void bindViewClickListener(BaseViewHolder holder, int position) {
        View view = holder.itemView;
        view.setOnClickListener(new OnMultiClickListener() {
            @Override
            protected void onMultiClick(@Nullable View v) {
                viewHolderDelegate.onItemClickListener(view, data.get(position), position);
            }
        });
        view.setOnLongClickListener(v -> viewHolderDelegate.onItemLongClickListener(view, data.get(position), position));
    }

    @Override
    public int getItemViewType(int position) {
        return viewHolderDelegate.getItemViewType(data.get(position), position);
    }

    private int getLayoutId(int viewType) {
        return mLayouts[viewType];
    }


}
