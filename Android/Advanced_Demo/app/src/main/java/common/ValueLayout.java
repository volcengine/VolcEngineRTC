package common;

import android.content.Context;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.ss.rtc.demo.advanced.R;

public class ValueLayout extends RelativeLayout {

    private TextView mTitleTv;
    private TextView mValueTv;
    private ImageView mArrowIv;

    public ValueLayout(Context context) {
        super(context);
        initView();
    }

    public ValueLayout(Context context, AttributeSet attrs) {
        super(context, attrs);
        initView();
    }

    public ValueLayout(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        initView();
    }

    private void initView() {
        LayoutInflater.from(getContext()).inflate(R.layout.layout_value, this, true);
        mTitleTv = findViewById(R.id.left_tv);
        mValueTv = findViewById(R.id.right_tv);
        mArrowIv = findViewById(R.id.arrow_iv);
    }

    public void setTitle(String title) {
        mTitleTv.setText(title);
    }

    public void setValue(String value) {
        mValueTv.setText(value);
    }

    public void showArrow(boolean isShowing) {
        mArrowIv.setVisibility(isShowing ? View.VISIBLE : View.INVISIBLE);
    }
}
