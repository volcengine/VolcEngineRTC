package common;

import android.content.Context;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.annotation.Nullable;

import com.ss.rtc.demo.advanced.R;


public class SubTitleLayout extends LinearLayout {

    private TextView mTitleTv;

    public SubTitleLayout(Context context) {
        super(context);
        initView();
    }

    public SubTitleLayout(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        initView();
    }

    public SubTitleLayout(Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        initView();
    }

    private void initView() {
        LayoutInflater.from(getContext()).inflate(R.layout.layout_subtitle, this, true);
        mTitleTv = findViewById(R.id.title);
    }

    public void setTitle(String title) {
        mTitleTv.setText(title);
    }
}
