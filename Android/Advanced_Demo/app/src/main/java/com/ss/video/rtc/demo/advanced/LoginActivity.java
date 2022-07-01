package com.ss.video.rtc.demo.advanced;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;

import android.Manifest;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.text.TextUtils;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.ss.bytertc.engine.RTCEngine;
import com.ss.rtc.demo.advanced.R;
import com.ss.video.rtc.demo.advanced.utils.CommonUtil;

import java.util.regex.Pattern;

/**
 * VolcEngineRTC 音视频通话入口页面
 * <p>
 * 包含如下简单功能：
 * - 该页面用来跳转至音视频通话主页面
 * - 申请相关权限
 * - 校验房间名和用户名
 * - 展示当前 SDK 使用的版本号 {@link RTCEngine#getSdkVersion()}
 * <p>
 * 有以下常见的注意事项：
 * 1.SDK必要的权限有：外部内存读写、摄像头权限、麦克风权限，其余完整的权限参见{@link src/main/AndroidManifest.xml}。
 * 没有这些权限不会导致崩溃，但是会影响SDK的正常使用。
 * 2.SDK 对房间名、用户名的限制是：非空且最大长度不超过128位的数字、大小写字母、@ . _ \ -
 */
public class LoginActivity extends AppCompatActivity implements View.OnClickListener {
    private static final int PERMISSIONS_REQUEST_CODE = 1000;
    private Context mContext;
    private EditText mRoomInput;
    private EditText mUserInput;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);
        mContext = getApplicationContext();
        TextView title = findViewById(R.id.title_bar_title_tv);
        title.setText(R.string.login);
        mRoomInput = findViewById(R.id.room_id_input);
        mUserInput = findViewById(R.id.user_id_input);
        findViewById(R.id.join_room_btn).setOnClickListener(this);
        findViewById(R.id.setting_btn_tv).setOnClickListener(this);
        // 获取当前SDK的版本号
        String sdkVersion = RTCEngine.getSdkVersion();
        TextView versionTv = findViewById(R.id.version_tv);
        versionTv.setText(String.format("VolcEngineRTC v%s", sdkVersion));

        ActivityCompat.requestPermissions(this,
                new String[]{Manifest.permission.CAMERA,
                        Manifest.permission.RECORD_AUDIO},
                PERMISSIONS_REQUEST_CODE);
    }

    private void joinChannel(String roomId, String userId) {
        if (TextUtils.isEmpty(roomId)) {
            Toast.makeText(this, "房间号不能为空", Toast.LENGTH_SHORT).show();
            return;
        }
        if (TextUtils.isEmpty(userId)) {
            Toast.makeText(this, "用户名不能为空", Toast.LENGTH_SHORT).show();
            return;
        }
        if (!Pattern.matches(Constants.INPUT_REGEX, roomId)) {
            Toast.makeText(this, "房间号格式错误", Toast.LENGTH_SHORT).show();
            return;
        }
        if (!Pattern.matches(Constants.INPUT_REGEX, userId)) {
            Toast.makeText(this, "用户名格式错误", Toast.LENGTH_SHORT).show();
            return;
        }
        Intent intent = new Intent(this, RTCRoomActivity.class);
        intent.putExtra(Constants.ROOM_ID_EXTRA, roomId);
        intent.putExtra(Constants.USER_ID_EXTRA, userId);
        startActivity(intent);
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        if (requestCode == PERMISSIONS_REQUEST_CODE) {
            int len = permissions.length;
            if (len == 0) {
                return;
            }
            for (int i = 0; i < len; i++) {
                if (TextUtils.equals(permissions[i], Manifest.permission.CAMERA)
                        && grantResults[i] != PackageManager.PERMISSION_GRANTED) {
                    CommonUtil.showShortToast(mContext, R.string.login_activity_permission_deny_hint_for_camera);
                }
                if (TextUtils.equals(permissions[i], Manifest.permission.RECORD_AUDIO)
                        && grantResults[i] != PackageManager.PERMISSION_GRANTED) {
                    CommonUtil.showShortToast(mContext, R.string.login_activity_permission_deny_hint_for_audio);
                }
            }
        }
    }

    @Override
    public void onClick(View view) {
        int id = view.getId();
        if (id == R.id.join_room_btn) {
            String roomId = mRoomInput.getText().toString();
            String userId = mUserInput.getText().toString();
            joinChannel(roomId, userId);
        } else if (id == R.id.setting_btn_tv) {
            PreJoinSettingsDialog settingsDialog = new PreJoinSettingsDialog();
            FragmentManager fragmentManager = getSupportFragmentManager();
            FragmentTransaction ft = fragmentManager.beginTransaction();
            ft.add(settingsDialog, PreJoinSettingsDialog.TAG_FOR_SHOW);
            ft.commitAllowingStateLoss();
        }
    }
}