package rtc.volcengine.apiexample.examples;

import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.TextureView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import com.ss.bytertc.engine.RTCRoom;
import com.ss.bytertc.engine.RTCRoomConfig;
import com.ss.bytertc.engine.RTCEngine;
import com.ss.bytertc.engine.UserInfo;
import com.ss.bytertc.engine.VideoCanvas;
import com.ss.bytertc.engine.data.EngineConfig;
import com.ss.bytertc.engine.data.StreamInfo;
import com.ss.bytertc.engine.handler.IRTCRoomEventHandler;
import com.ss.bytertc.engine.handler.IRTCEngineEventHandler;
import com.ss.bytertc.engine.type.ChannelProfile;

import java.util.regex.Pattern;

import rtc.volcengine.apiexample.BaseActivity;
import rtc.volcengine.apiexample.R;
import rtc.volcengine.apiexample.Utils.ToastUtil;
import rtc.volcengine.apiexample.common.Constants;
import rtc.volcengine.apiexample.common.annotations.ApiExample;

/**
 * 功能名称： ByteRTC 多房间
 * 功能简单描述：你可能需要让同一个用户加入多个 RTC 房间，同时收听/收看不同房间中的音视频，并在其中一个房间中发布音视频
 * 参考文档： https://www.volcengine.com/docs/6348/196844
 *
 * 此功能涉及的API及回调：
 *     createRTCEngine 创建引擎
 *     destroyRTCEngine 销毁引擎
 *     startAudioCapture 开启音频采集
 *     startVideoCapture 开启视频采集
 *     createRTCRoom 创建RTC房间
 *     joinRoom 进入RTC房间
 *     leaveRoom 离开RTC房间
 *     destroy 销毁RTC房间
 *     setLocalVideoCanvas 设置本地视频渲染视图
 *     setRemoteVideoCanvas 设置远端视频渲染视图
 *
 *     onRoomStateChanged 房间状态回调
 *     onLeaveRoom 离房回调
 *     onUserJoined 用户加入回调
 *     onUserLeave  用户离开回调
 *
 * Demo实现时的逻辑
 *    为了展示简单，所有功能的token都由客户端生成，请在真正接入时视具体情况而定
 *    本Demo演示功能：仅展示3个视频窗口，第一行展示本地采集画面，第二行分别展示room1 远端用户和room2远端用户
 */

@ApiExample(order = 1, category = "房间管理", name = "多房间MultiRoom")
public class MultiRoomActivity extends BaseActivity {

    private static final String TAG = "MultiRoomActivity";

    private TextureView localView;
    private TextureView firstRoomRemoteView;
    private TextureView secondRoomRemoteView;
    private EditText roomIdEt1;
    private EditText roomIdEt2;
    private Button joinRoomBtn1;
    private Button joinRoomBtn2;
    private TextView localUserName;
    private TextView remoteUserName1;
    private TextView remoteUserName2;

    RTCEngine rtcVideo;

    RTCRoom rtcRoom1;
    RTCRoom rtcRoom2;
    boolean isJoinFirstRoom;
    boolean isJoinSecondRoom;
    private String roomID1;
    private String roomID2;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_multi_room);
        setTitle(R.string.title_multi_room);
        initUI();

        // 初始化引擎
        EngineConfig config = new EngineConfig();
        config.context = this;
        config.appID = Constants.APP_ID;
        rtcVideo = RTCEngine.createRTCEngine(config, videoEventHandler);
        // 设置本地视频渲染视图
        setLocalRenderView();
        // 开启音视频采集
        rtcVideo.startAudioCapture();
        rtcVideo.startVideoCapture();

    }

    private void initUI() {
        localView = findViewById(R.id.local_view);
        firstRoomRemoteView = findViewById(R.id.remote_view1);
        secondRoomRemoteView = findViewById(R.id.remote_view2);
        localUserName = findViewById(R.id.local_user_name);
        remoteUserName1 = findViewById(R.id.remote_user_name1);
        remoteUserName2 = findViewById(R.id.remote_user_name2);

        roomIdEt1 = findViewById(R.id.room1_input);
        roomIdEt2 = findViewById(R.id.room2_input);

        joinRoomBtn1 = findViewById(R.id.btn_join_room_1);
        joinRoomBtn1.setOnClickListener(v -> {
            if (isJoinFirstRoom) {
                leaveFirstRoom();
                isJoinFirstRoom = false;
            } else {
                String roomId = roomIdEt1.getText().toString();
                if (!TextUtils.isEmpty(roomId)) {
                    joinFirstRoom(roomId);
                } else {
                    ToastUtil.showAlert(this,"房间号为空");
                }
                isJoinFirstRoom = true;
            }
        });
        joinRoomBtn2 = findViewById(R.id.btn_join_room_2);
        joinRoomBtn2.setOnClickListener(v -> {
            if (isJoinSecondRoom) {
                leaveSecondRoom();
                isJoinSecondRoom = false;
            } else {
                String roomid = roomIdEt2.getText().toString();
                if (!TextUtils.isEmpty(roomid)) {
                    joinSecondRoom(roomid);
                } else {
                    ToastUtil.showAlert(this,"房间号为空");
                }
                isJoinSecondRoom = true;
            }
        });

    }

    /**
     * 设置本地渲染视图，支持TextureView和SurfaceView
     */
    private void setLocalRenderView() {
        VideoCanvas videoCanvas = new VideoCanvas();
        videoCanvas.renderView = localView;
        videoCanvas.renderMode = VideoCanvas.RENDER_MODE_HIDDEN;
        // 设置本地视频渲染视图
        rtcVideo.setLocalVideoCanvas(videoCanvas);
    }

    /**
     * 加入房间1
     */
    public void joinFirstRoom(String roomID) {
        if (!Pattern.matches(INPUT_REGEX, roomID)) {
            ToastUtil.showAlert(this, "输入不合法，只支持数字、大小写字母、@._-");
            return;
        }
        this.roomID1 = roomID;

        String token = requestRoomToken(roomID);
        rtcRoom1 = rtcVideo.createRTCRoom(roomID);
        /**
         * 回调线程不在主线程，如果有UI操作需要转到主线程进行
         */
        rtcRoom1.setRTCRoomEventHandler(firstRoomEventHandler);

        // 用户信息
        UserInfo userInfo = new UserInfo(localUid, "");
        // 房间配置
        boolean isAutoPublishAudio = true;
        boolean isAutoPublishVideo = true;
        boolean isAutoSubscribeAudio = true;
        boolean isAutoSubscribeVideo = true;
        RTCRoomConfig roomConfig = new RTCRoomConfig(ChannelProfile.CHANNEL_PROFILE_CHAT_ROOM, "", isAutoPublishAudio, isAutoPublishVideo, isAutoSubscribeAudio, isAutoSubscribeVideo);
        // 加入房间
        rtcRoom1.joinRoom(token, userInfo, true, roomConfig);
    }

    /**
     * 加入房间2
     */
    public void joinSecondRoom(String roomID) {
        if (!Pattern.matches(INPUT_REGEX, roomID)) {
            ToastUtil.showAlert(this, "输入不合法，只支持数字、大小写字母、@._-");
            return;
        }

        String token = requestRoomToken(roomID);

        this.roomID2  = roomID;
        rtcRoom2 = rtcVideo.createRTCRoom(roomID);
        rtcRoom2.setRTCRoomEventHandler(secondRoomEventHandler);
        // 用户信息
        UserInfo userInfo = new UserInfo(localUid, "");
        // room2不发流
        boolean isAutoPublishAudio = false;
        boolean isAutoPublishVideo = false;
        boolean isAutoSubscribeAudio = true;
        boolean isAutoSubscribeVideo = true;
        RTCRoomConfig roomConfig = new RTCRoomConfig(ChannelProfile.CHANNEL_PROFILE_CHAT_ROOM, "", isAutoPublishAudio, isAutoPublishVideo, isAutoSubscribeAudio, isAutoSubscribeVideo);
        // 加入房间
        int ret = rtcRoom2.joinRoom(token, userInfo, true, roomConfig);
        if (ret != 0) {
            ToastUtil.showAlert(this, "加入房间失败, ret : " + ret);
        }
    }

    public void leaveFirstRoom() {
        if (rtcRoom1 != null) {
            rtcRoom1.leaveRoom();
            rtcRoom1.destroy();
            rtcRoom1 = null;
        }
        joinRoomBtn1.setText("加入房间");
    }

    public void leaveSecondRoom() {
        if (rtcRoom2 != null) {
            rtcRoom2.leaveRoom();
            rtcRoom2.destroy();
            rtcRoom2 = null;
        }
        joinRoomBtn2.setText("加入房间");
    }

    private final IRTCRoomEventHandler firstRoomEventHandler = new IRTCRoomEventHandler() {
        @Override
        public void onRoomStateChanged(String roomId, String uid, int state, String extraInfo) {
            super.onRoomStateChanged(roomId, uid, state, extraInfo);
            String info = String.format("onRoomStateChanged,roomId:%s, uid:%s, state:%d, extraInfo:%s", roomId, uid, state, extraInfo);
            Log.i(TAG, "room1: " + info);
            runOnUiThread(() -> {
                if (state == 0) {
                    // 进房成功
                    joinRoomBtn1.setText("退出房间");
                    localUserName.setText(uid);
                }
                ToastUtil.showLongToast(MultiRoomActivity.this, info);
            });
        }
        @Override
        public void onUserPublishStreamVideo(String streamId, StreamInfo streamInfo, boolean isPublish) {
            String info = String.format("onUserPublishStreamVideo, roomId:%s, uid:%s, isPublish:%b", streamInfo.roomId, streamInfo.userId, isPublish);
            Log.i(TAG, "room1: " + info);
            if (isPublish) {
                ToastUtil.showLongToast(MultiRoomActivity.this, info);
                runOnUiThread(() -> {
                    // 设置远端视频渲染视图
                    VideoCanvas videoCanvas = new VideoCanvas();
                    videoCanvas.renderView = firstRoomRemoteView;
                    videoCanvas.renderMode = VideoCanvas.RENDER_MODE_HIDDEN;
                    rtcVideo.setRemoteVideoCanvas(streamId, videoCanvas);
                    remoteUserName1.setText(streamInfo.userId);
                });
            } else {
                runOnUiThread(() -> {
                    // 解除远端视频渲染视图绑定
                    rtcVideo.setRemoteVideoCanvas(streamId, null);
                    remoteUserName1.setText("");
                });
            }

        }
        @Override
        public void onUserPublishStreamAudio(String streamId, StreamInfo streamInfo, boolean isPublish) {
            String info = String.format("onUserPublishStreamAudio, roomId:%s, uid:%s, isPublish:%b", streamInfo.roomId, streamInfo.userId, isPublish);
            ToastUtil.showShortToast(MultiRoomActivity.this, info);
            Log.i(TAG, "room1: " + info);
        }

        @Override
        public void onUserLeave(String uid, int reason) {
            super.onUserLeave(uid, reason);
            String info = String.format("onUserLeave, roomId:%s, uid:%s, reason:%s", roomID1, uid, reason + "");
            ToastUtil.showShortToast(MultiRoomActivity.this, info);
        }

        @Override
        public void onUserJoined(UserInfo userInfo) {
            super.onUserJoined(userInfo);
            String info = String.format("onUserJoined, uid:%s", userInfo.uid);
            ToastUtil.showShortToast(MultiRoomActivity.this, info);
        }
    };

    private final IRTCRoomEventHandler secondRoomEventHandler = new IRTCRoomEventHandler() {
        @Override
        public void onRoomStateChanged(String roomId, String uid, int state, String extraInfo) {
            super.onRoomStateChanged(roomId, uid, state, extraInfo);
            String info = String.format("onRoomStateChanged, roomId:%s, uid:%s, state:%d, extraInfo:%s", roomId, uid, state, extraInfo);
            runOnUiThread(() -> {
                if (state == 0) {
                    joinRoomBtn2.setText("退出房间");
                }
                ToastUtil.showLongToast(MultiRoomActivity.this, info);
            });
            Log.i(TAG, "room2: " + info);
        }

        @Override
         public void onUserPublishStreamVideo(String streamId, StreamInfo streamInfo, boolean isPublish) {
            String info = String.format("onUserPublishStreamVideo, roomId:%s, uid:%s, isPublish:%b", streamInfo.roomId, streamInfo.userId, isPublish);
            if (isPublish) {
                ToastUtil.showShortToast(MultiRoomActivity.this, info);
                runOnUiThread(() -> {
                    // 设置房间二远端用户视图
                    VideoCanvas videoCanvas = new VideoCanvas();
                    videoCanvas.renderView = secondRoomRemoteView;
                    videoCanvas.renderMode = VideoCanvas.RENDER_MODE_HIDDEN;
                    rtcVideo.setRemoteVideoCanvas(streamId, videoCanvas);
                    remoteUserName2.setText(streamInfo.userId);
                });
            } else {
                runOnUiThread(() -> {
                    // 解除远端视频渲染视图绑定
                    rtcVideo.setRemoteVideoCanvas(streamId, null);
                    remoteUserName2.setText("");
                });
            }
            Log.i(TAG, "room2: " + info);

        }

        @Override
        public void onUserPublishStreamAudio(String streamId, StreamInfo streamInfo, boolean isPublish) {
            String info = String.format("onUserPublishStreamAudio, roomId:%s, uid:%s, isPublish:%b", streamInfo.roomId, streamInfo.userId, isPublish);
            ToastUtil.showShortToast(MultiRoomActivity.this, info);
            Log.i(TAG, "room2: " + info);
        }

        @Override
        public void onUserLeave(String uid, int reason) {
            super.onUserLeave(uid, reason);
            String info = String.format("onUserLeave, roomId:%s, uid:%s, reason:%s", roomID2, uid, reason + "");
            ToastUtil.showShortToast(MultiRoomActivity.this, info);
        }

        @Override
        public void onUserJoined(UserInfo userInfo) {
            super.onUserJoined(userInfo);
            String info = String.format("onUserJoined, uid:%s", userInfo.uid);
            ToastUtil.showShortToast(MultiRoomActivity.this, info);
        }
    };

    private final IRTCEngineEventHandler videoEventHandler = new IRTCEngineEventHandler() {
        @Override
        public void onWarning(int warn) {
            super.onWarning(warn);
            runOnUiThread(() -> ToastUtil.showLongToast(MultiRoomActivity.this, "onWarning:" + warn));

        }

        @Override
        public void onError(int err) {
            super.onError(err);
            runOnUiThread(() -> ToastUtil.showLongToast(MultiRoomActivity.this, "onError:" + err));
        }
    };

    @Override
    protected void onDestroy() {
        super.onDestroy();
        if (rtcVideo != null) {
            rtcVideo.stopAudioCapture();
            rtcVideo.stopVideoCapture();
        }
        RTCEngine.destroyRTCEngine();
    }
}