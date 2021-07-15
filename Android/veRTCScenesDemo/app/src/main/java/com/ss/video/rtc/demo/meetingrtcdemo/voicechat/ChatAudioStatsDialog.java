package com.ss.video.rtc.demo.meetingrtcdemo.voicechat;

import android.content.Context;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatDialog;

import com.ss.video.rtc.demo.basic_module.utils.WindowUtils;
import com.ss.video.rtc.demo.meetingrtcdemo.R;
import com.ss.video.rtc.demo.meetingrtcdemo.core.eventbus.MeetingEventManager;
import com.ss.video.rtc.engine.handler.IRtcEngineEventHandler;

import org.greenrobot.eventbus.Subscribe;
import org.greenrobot.eventbus.ThreadMode;

public class ChatAudioStatsDialog extends AppCompatDialog {

    private final View mView;
    private final TextView mAudioChannel;
    private final TextView mUploadSampleRate;
    private final TextView mUploadBitrate;
    private final TextView mUploadLossRate;
    private final TextView mDownloadBitrate;
    private final TextView mDownloadLossRate;
    private final TextView mDelay;

    public ChatAudioStatsDialog(Context context) {
        super(context, R.style.CommonDialog);
        setCancelable(true);

        mView = LayoutInflater.from(getContext()).inflate(R.layout.dialog_voice_audio_stats, null);
        mView.findViewById(R.id.dialog_voice_audio_stats_hover).setOnClickListener(v -> dismiss());
        mView.findViewById(R.id.dialog_voice_audio_stats_close).setOnClickListener(v -> dismiss());
        mAudioChannel = mView.findViewById(R.id.dialog_voice_audio_channel_value);
        mUploadSampleRate = mView.findViewById(R.id.dialog_voice_audio_upload_sample_rate_value);
        mUploadBitrate = mView.findViewById(R.id.dialog_voice_audio_upload_bitrate_value);
        mUploadLossRate = mView.findViewById(R.id.dialog_voice_audio_upload_loss_rate_value);
        mDownloadBitrate = mView.findViewById(R.id.dialog_voice_audio_download_bitrate_value);
        mDownloadLossRate = mView.findViewById(R.id.dialog_voice_audio_download_loss_rate_value);
        mDelay = mView.findViewById(R.id.dialog_voice_audio_delay_value);

        onLocalAudioStats(new IRtcEngineEventHandler.LocalAudioStats());
    }

    @Override
    public void show() {
        super.show();
        WindowManager.LayoutParams params = getWindow().getAttributes();
        params.width = WindowUtils.getScreenWidth(getContext());
        params.height = ViewGroup.LayoutParams.MATCH_PARENT;
        getWindow().setAttributes(params);
        getWindow().setContentView(mView, new ViewGroup.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT,
                ViewGroup.LayoutParams.MATCH_PARENT));

        MeetingEventManager.register(this);
    }

    @Override
    public void dismiss() {
        super.dismiss();
        MeetingEventManager.unregister(this);
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onLocalAudioStats(IRtcEngineEventHandler.LocalAudioStats event) {
        mAudioChannel.setText(String.valueOf(event.numChannels));
        mUploadSampleRate.setText(String.valueOf(event.sentSampleRate));
        mUploadBitrate.setText((int) event.sendKBitrate + "kbps");
        mUploadLossRate.setText((int) event.audioLossRate + "%");
        mDownloadBitrate.setText("0kbps");
        mDownloadLossRate.setText("0%");
        mDelay.setText(event.rtt + "ms");
    }
}
