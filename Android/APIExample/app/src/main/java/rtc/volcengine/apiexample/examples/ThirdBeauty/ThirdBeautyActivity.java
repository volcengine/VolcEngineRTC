package rtc.volcengine.apiexample.examples.ThirdBeauty;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.AppCompatButton;

import android.content.Intent;
import android.os.Bundle;

import rtc.volcengine.apiexample.R;
import rtc.volcengine.apiexample.common.annotations.ApiExample;
import rtc.volcengine.apiexample.examples.AudioMixing.AudioEffectMixingActivity;
import rtc.volcengine.apiexample.examples.AudioMixing.AudioMediaMixingActivity;
import rtc.volcengine.apiexample.examples.AudioMixing.AudioMixingActivity;
import rtc.volcengine.apiexample.examples.ThirdBeauty.Fubeauty.FuBeautyActivity;
import rtc.volcengine.apiexample.examples.ThirdBeauty.byteBeauty.ByteBeautyActivity;

@ApiExample(name = "第三方美颜", order = 9, category = "重要组件")
public class ThirdBeautyActivity extends AppCompatActivity {

    AppCompatButton btnByteBeauty;
    AppCompatButton btnFuBeauty;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_third_beauty);
        setTitle(R.string.title_third_beauty);

        btnByteBeauty = findViewById(R.id.btn_byte_beauty);
        btnByteBeauty.setOnClickListener(v -> startActivity(new Intent(ThirdBeautyActivity.this, ByteBeautyActivity.class)));

        btnFuBeauty = findViewById(R.id.btn_fu_beauty);
        btnFuBeauty.setOnClickListener(v -> startActivity(new Intent(ThirdBeautyActivity.this, FuBeautyActivity.class)));
    }
}