package rtc.volcengine.apiexample;

import android.Manifest;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.content.ContextCompat;

import com.google.android.material.tabs.TabLayout;

import java.util.Random;

import rtc.volcengine.apiexample.common.Constants;
import rtc.volcengine.apiexample.common.accesstoken.AccessToken;
import rtc.volcengine.apiexample.common.accesstoken.Utils;

public class BaseActivity extends AppCompatActivity {

    public String localUid;
    // INPUT_REGEX SDK 对房间名、用户名的限制是：非空且最大长度不超过128位的数字、大小写字母、@ . _ -
    public static final String INPUT_REGEX = "^[a-zA-Z0-9@._-]{1,128}$";

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        localUid = "user_" + new Random().nextInt(1000);
        requestPermission();
    }

    public void requestPermission() {
        String[] PERMISSIONS_STORAGE = {
                Manifest.permission.RECORD_AUDIO,
                Manifest.permission.CAMERA};

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            if (ContextCompat.checkSelfPermission(this, "android.permission.CAMERA") != PackageManager.PERMISSION_GRANTED
                    || ContextCompat.checkSelfPermission(this, "android.permission.RECORD_AUDIO") != PackageManager.PERMISSION_GRANTED) {
                requestPermissions(PERMISSIONS_STORAGE, 22);
            }
        }
    }

    public String requestRoomToken(String roomId) {
        if (TextUtils.isEmpty(Constants.APP_ID) || TextUtils.isEmpty(Constants.APP_KEY)) {
            return "";
        }
        AccessToken token = new AccessToken(Constants.APP_ID, Constants.APP_KEY, roomId, localUid);
        token.ExpireTime(Utils.getTimestamp() + 3600);
        token.AddPrivilege(AccessToken.Privileges.PrivSubscribeStream, 0);
        token.AddPrivilege(AccessToken.Privileges.PrivPublishStream, Utils.getTimestamp() + 3600);


        String s = token.Serialize();
        Log.d("BaseActivity", "token: " + s);
        return s;
    }

}
