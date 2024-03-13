package rtc.volcengine.apiexample.examples.AudioMixing;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.AppCompatButton;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;

import rtc.volcengine.apiexample.R;
import rtc.volcengine.apiexample.common.annotations.ApiExample;

@ApiExample(order = 4, name = "音乐混音")
public class AudioMixingActivity extends AppCompatActivity {
    Button btnAudioFileMixing;
    Button btnPCMMixing;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_audio_mixing);
        setTitle(R.string.title_audio_mixing);

        btnAudioFileMixing = findViewById(R.id.btn_audio_effect_mixing);
        btnAudioFileMixing.setOnClickListener(v -> startActivity(new Intent(AudioMixingActivity.this, AudioEffectMixingActivity.class)));

        btnPCMMixing = findViewById(R.id.btn_audio_media_mixing);
        btnPCMMixing.setOnClickListener(v -> startActivity(new Intent(AudioMixingActivity.this, AudioMediaMixingActivity.class)));
    }
}