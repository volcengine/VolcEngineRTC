package com.ss.video.rtc.demo.advanced.effects.view;

import android.annotation.SuppressLint;
import android.content.Context;
import android.text.TextUtils;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.SeekBar;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.constraintlayout.widget.ConstraintLayout;
import androidx.recyclerview.widget.GridLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.ss.rtc.demo.advanced.R;
import com.ss.video.rtc.demo.advanced.effects.EffectNodeCallback;
import com.ss.video.rtc.demo.advanced.effects.model.EffectSection;
import com.ss.video.rtc.demo.advanced.effects.model.EffectNode;

import java.util.ArrayList;
import java.util.List;

/**
 * 美颜功能的布局
 * 展示的信息包括：强度设置、具体美颜功能列表
 *
 * 主要方法：
 * 设置具体美颜功能：setBeautyNodes(List<EffectNode> beautyNodes, boolean hasProgress)
 * 是否支持反选：setSupportUnSelected(boolean isSupportUnSelected)
 *
 * 实现接口：
 * interface BeautyViewCallback
 *
 * 支持配置：
 * isSupportUnSelected 是否支持反选
 */
public class EffectLayout extends ConstraintLayout {

    // 是否支持反选
    private boolean mIsSupportUnSelected = false;

    private TextView mBeautySeekbarTitle;
    private SeekBar mBeautySeekbar;
    private EffectNodeAdapter mEffectNodeAdapter;
    private final List<EffectNode> mEffectNodeList = new ArrayList<>();
    private EffectNodeCallback mEffectNodeCallback;

    private final INodeClick mINodeClick = new INodeClick() {
        @SuppressLint("NotifyDataSetChanged")
        @Override
        public void onClick(EffectNode node) {
            for (EffectNode temp : mEffectNodeList) {
                if (mIsSupportUnSelected) {
                    temp.selected = TextUtils.equals(temp.key, node.key) && temp.selected;
                } else {
                    temp.selected = TextUtils.equals(temp.key, node.key);
                }
            }

            mEffectNodeAdapter.notifyDataSetChanged();
            mBeautySeekbar.setProgress((int) (node.value * 100));

            EffectNodeCallback callback = mEffectNodeCallback;
            if (callback != null) {
                callback.onEffectClicked(node);
            }
        }
    };

    private final SeekBar.OnSeekBarChangeListener mOnSeekBarChangeListener = new SeekBar.OnSeekBarChangeListener() {
        @Override
        public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
            for (EffectNode node : mEffectNodeList) {
                if (node.selected) {
                    node.value = ((float) progress) / 100;
                    EffectNodeCallback callback = mEffectNodeCallback;
                    if (callback != null) {
                        callback.onEffectValueChanged(node);
                    }
                    break;
                }
            }
        }

        @Override
        public void onStartTrackingTouch(SeekBar seekBar) {

        }

        @Override
        public void onStopTrackingTouch(SeekBar seekBar) {

        }
    };

    public EffectLayout(@NonNull Context context) {
        super(context);
        initView();
    }

    public EffectLayout(@NonNull Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        initView();
    }

    public EffectLayout(@NonNull Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        initView();
    }

    private void initView() {
        LayoutInflater.from(getContext()).inflate(R.layout.layout_beauty, this, true);
        mBeautySeekbarTitle = findViewById(R.id.beauty_seekbar_title);
        mBeautySeekbar = findViewById(R.id.beauty_seekbar);
        mBeautySeekbar.setOnSeekBarChangeListener(mOnSeekBarChangeListener);
        RecyclerView beautyNodesRV = findViewById(R.id.beauty_nodes);
        mEffectNodeAdapter = new EffectNodeAdapter((mINodeClick));
        beautyNodesRV.setLayoutManager(new GridLayoutManager(getContext(), 4));
        beautyNodesRV.setAdapter(mEffectNodeAdapter);
    }

    public void setEffectSection(EffectSection effectSection, EffectNodeCallback effectNodeCallback) {
        boolean hasProgress = effectSection.hasProgress;
        List<? extends EffectNode> beautyNodes = effectSection.effectNodes;
        mBeautySeekbarTitle.setVisibility(hasProgress ? VISIBLE : GONE);
        mBeautySeekbar.setVisibility(hasProgress ? VISIBLE : GONE);
        mBeautySeekbarTitle.setText(String.format("%s强度", effectSection.title));

        mEffectNodeList.clear();
        if (beautyNodes != null) {
            mEffectNodeList.addAll(beautyNodes);
            if (hasProgress) {
                for (EffectNode node : beautyNodes) {
                    if (node.selected) {
                        mBeautySeekbar.setProgress((int) (node.value * 100));
                        break;
                    }
                }
            }
        } else {
            mBeautySeekbar.setProgress(0);
        }
        mEffectNodeAdapter.setData(beautyNodes);
        mEffectNodeCallback = effectNodeCallback;
    }

    @SuppressLint("unused")
    public void setSupportUnSelected(boolean isSupportUnSelected) {
        this.mIsSupportUnSelected = isSupportUnSelected;
    }

    private static class EffectNodeAdapter extends RecyclerView.Adapter<BeautyNodeViewHolder> {

        private final List<EffectNode> mEffectNodeList = new ArrayList<>();
        private final INodeClick mINodeClick;

        @SuppressLint("NotifyDataSetChanged")
        public EffectNodeAdapter(INodeClick iNodeClick) {
            mINodeClick = iNodeClick;
        }

        @NonNull
        @Override
        public BeautyNodeViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
            return new BeautyNodeViewHolder(LayoutInflater.from(parent.getContext())
                            .inflate(R.layout.view_holder_beauty, parent, false),
                    mINodeClick);
        }

        @Override
        public void onBindViewHolder(@NonNull BeautyNodeViewHolder holder, int position) {
            holder.bind(mEffectNodeList.get(position));
        }

        @Override
        public int getItemCount() {
            return mEffectNodeList.size();
        }

        @SuppressLint("NotifyDataSetChanged")
        public void setData(List<? extends EffectNode> effectNodeList) {
            mEffectNodeList.clear();
            if (effectNodeList != null && !effectNodeList.isEmpty()) {
                mEffectNodeList.addAll(effectNodeList);
            }
            notifyDataSetChanged();
        }
    }

    private static class BeautyNodeViewHolder extends RecyclerView.ViewHolder {

        private EffectNode mEffectNode;

        public BeautyNodeViewHolder(@NonNull View itemView, INodeClick iNodeClick) {
            super(itemView);
            itemView.setOnClickListener((v) -> {
                if (mEffectNode != null && iNodeClick != null) {
                    mEffectNode.selected = !mEffectNode.selected;
                    iNodeClick.onClick(mEffectNode);
                }
            });
        }

        public void bind(EffectNode effectNode) {
            mEffectNode = effectNode;
            ((TextView) itemView).setText(effectNode.name);
            itemView.setSelected(effectNode.selected);
        }
    }

    private interface INodeClick {

        void onClick(EffectNode node);
    }
}
