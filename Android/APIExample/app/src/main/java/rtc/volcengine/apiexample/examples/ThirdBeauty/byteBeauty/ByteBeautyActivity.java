package rtc.volcengine.apiexample.examples.ThirdBeauty.byteBeauty;

import android.graphics.Color;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.TextureView;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;

import com.google.android.material.tabs.TabLayout;
import com.ss.bytertc.engine.RTCRoom;
import com.ss.bytertc.engine.RTCRoomConfig;
import com.ss.bytertc.engine.RTCVideo;
import com.ss.bytertc.engine.UserInfo;
import com.ss.bytertc.engine.VideoCanvas;
import com.ss.bytertc.engine.data.RemoteStreamKey;
import com.ss.bytertc.engine.data.StreamIndex;
import com.ss.bytertc.engine.data.VideoOrientation;
import com.ss.bytertc.engine.data.VirtualBackgroundSource;
import com.ss.bytertc.engine.data.VirtualBackgroundSourceType;
import com.ss.bytertc.engine.handler.IRTCRoomEventHandler;
import com.ss.bytertc.engine.handler.IRTCVideoEventHandler;
import com.ss.bytertc.engine.type.ChannelProfile;
import com.ss.bytertc.engine.type.MediaStreamType;
import com.ss.bytertc.engine.type.RTCRoomStats;
import com.ss.bytertc.engine.type.StreamRemoveReason;
import com.ss.bytertc.engine.video.IVideoEffect;

import java.io.File;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;

import rtc.volcengine.apiexample.BaseActivity;
import rtc.volcengine.apiexample.R;
import rtc.volcengine.apiexample.Utils.ToastUtil;
import rtc.volcengine.apiexample.common.Constants;

/**
 * 功能名称： VolcEngineRTC 字节美颜
 * 功能简单描述：通过视频自定义处理实现视频帧的美颜、美白、滤镜、贴纸等效果
 * 参考文档：https://www.volcengine.com/docs/6348/114717
 *
 * 此功能涉及的API及回调：
 *     createRTCVideo 创建引擎
 *     destroyRTCVideo 销毁引擎
 *     startAudioCapture 开启音频采集
 *     startVideoCapture 开启视频采集
 *     createRTCRoom 创建RTC房间
 *     joinRoom 进入RTC房间
 *     leaveRoom 离开RTC房间
 *     destroy 销毁RTC房间
 *     getVideoEffectInterface 获取视频特效接口
 *     setColorFilter 设置颜色滤镜
 *     setColorFilterIntensity 设置已启用颜色滤镜的强度
 *     setEffectNodes 设置视频特效素材包
 *     updateNode 设置特效强度
 *     getAuthMessage 从特效 SDK 获取授权消息，用于获取在线许可证
 *     freeAuthMessage 释放授权信息
 *     checkLicense 视频特效许可证检查
 *     setAlgoModelPath 设置视频特效算法模型路径
 *     enableEffect 开启关闭视频特效
 *
 *
 *
 *     onRoomStateChanged 房间状态回调
 *     onLeaveRoom 离房回调
 *     onUserJoined 用户加入回调
 *     onUserLeave  用户离开回调
 *     onUserPublishStream 用户发流回调
 *     onUserUnpublishStream 用户停止发流回调
 *
 *
 * 火山美颜集成参考：https://www.volcengine.com/docs/6348/114717
 * 本功能需付费使用，请联系美颜技术支持团队获取 v4.4.2+ 的 Standard/Lite 版本特效 SDK 及符合业务功能需求的 License 和素材资源包。
 * 申请付费使用后：
 * 1. 修改demo Constants.java 中 BYTE_EFFECT_LIC_NAME 为您开通的美颜证书名字
 * 2. 将资源模型放在 assets 目录中
 * 3. 修改build.gradle，将包名更换为与证书绑定的包名
 *
 * Demo实现时的逻辑
 *    本Demo演示功能：字节美颜
 *    为了展示简单，所有功能的token都由客户端生成，请在真正接入时视具体情况而定
 */
public class ByteBeautyActivity extends BaseActivity {

    private static final String TAG = "ByteBeautyActivity";
    private static final String roomID = "beauty_room";
    private FrameLayout localViewContainer;
    private FrameLayout effectLayoutContainer;
    private FrameLayout[] remoteContainers = new FrameLayout[3];
    private HashMap<String, Integer> remoteUserViewMap = new HashMap<>();
    private boolean[] isRemoteViewUsed = new boolean[3];
    private TabLayout tabLayout;
    private RTCVideo rtcVideo;
    private RTCRoom rtcRoom;
    private IVideoEffect rtcVideoEffect;
    private EffectResourceManager effectResourceManager;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_byte_beauty);
        setTitle(R.string.title_byte_beauty);
        initUI();
        effectResourceManager = new EffectResourceManager(this);
        effectResourceManager.initVideoEffectResource();
        

        // 创建引擎
        rtcVideo = RTCVideo.createRTCVideo(this, Constants.APP_ID, videoEventHandler, null, null);
        // 设置本端渲染视图
        setLocalRenderView();
        // 开启音视频采集
        rtcVideo.startVideoCapture();
        rtcVideo.startAudioCapture();
        rtcVideo.setVideoOrientation(VideoOrientation.PORTRAIT);

        initEffect();
        joinRoom(roomID);
    }

    private void initUI() {
        localViewContainer = findViewById(R.id.local_view_container);
        remoteContainers[0] = findViewById(R.id.remote_view_container1);
        remoteContainers[1] = findViewById(R.id.remote_view_container2);
        remoteContainers[2]= findViewById(R.id.remote_view_container3);

        tabLayout = findViewById(R.id.tab_layout);
        effectLayoutContainer = findViewById(R.id.effect_beauty_layout_container);

        final List<EffectSection> effectSectionList = new LinkedList<>();
        effectSectionList.add(getBeautySection());
        effectSectionList.add(getFilterSection());
        effectSectionList.add(getStickerSection());
        effectSectionList.add(getVirtualBackgroundSection());
        for (EffectSection section : effectSectionList) {
            tabLayout.addTab(tabLayout.newTab().setText(section.title));

            EffectLayout effectLayout = new EffectLayout(this);
            effectLayout.setTag(section.title);
            effectLayout.setEffectSection(section, effectNodeCallback);
            FrameLayout.LayoutParams layoutParams = new FrameLayout.LayoutParams(
                    ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
            effectLayoutContainer.addView(effectLayout, layoutParams);
            effectLayout.setVisibility(View.GONE);
        }

        tabLayout.addOnTabSelectedListener(new TabLayout.OnTabSelectedListener() {
            @Override
            public void onTabSelected(TabLayout.Tab tab) {
                setTabViewVisibility(tab, true);
            }

            @Override
            public void onTabUnselected(TabLayout.Tab tab) {
                setTabViewVisibility(tab, false);
            }

            @Override
            public void onTabReselected(TabLayout.Tab tab) {

            }
        });

        View view = effectLayoutContainer.getChildAt(0);
        if (view != null) {
            view.setVisibility(View.VISIBLE);
        }

    }

    private void setTabViewVisibility(TabLayout.Tab tab, boolean visible) {
        String tabTitle = tab.getText() == null ? "" : tab.getText().toString();
        for (int i = 0; i < effectLayoutContainer.getChildCount(); i++) {
            View view = effectLayoutContainer.getChildAt(i);
            String tag = view.getTag().toString();
            view.setVisibility(TextUtils.equals(tabTitle, tag) && visible ? View.VISIBLE : View.GONE);
        }
    }

    /**
     * 设置本地渲染视图，支持TextureView和SurfaceView
     */
    private void setLocalRenderView() {
        TextureView textureView = new TextureView(this);
        localViewContainer.removeAllViews();
        localViewContainer.addView(textureView);

        VideoCanvas videoCanvas = new VideoCanvas();
        videoCanvas.renderView = textureView;
        videoCanvas.renderMode = VideoCanvas.RENDER_MODE_HIDDEN;
        // 设置本地视频渲染视图
        rtcVideo.setLocalVideoCanvas(StreamIndex.STREAM_INDEX_MAIN, videoCanvas);
    }

    private void setRemoteRenderView(String uid) {
        for (int i = 0; i < isRemoteViewUsed.length; i++) {
            if (!isRemoteViewUsed[i]) {
                isRemoteViewUsed[i] = true;
                remoteUserViewMap.put(uid, i);

                TextureView textureView = new TextureView(this);
                remoteContainers[i].removeAllViews();
                remoteContainers[i].addView(textureView);

                RemoteStreamKey remoteStreamKey = new RemoteStreamKey(roomID, uid, StreamIndex.STREAM_INDEX_MAIN);
                VideoCanvas videoCanvas = new VideoCanvas();
                videoCanvas.renderView = textureView;
                videoCanvas.renderMode = VideoCanvas.RENDER_MODE_HIDDEN;
                rtcVideo.setRemoteVideoCanvas(remoteStreamKey, videoCanvas);
                break;
            }
        }
    }

    private void removeRemoteView(String uid) {
        int index = remoteUserViewMap.get(uid);
        if (index >= 0 && index < 3) {
            remoteContainers[index].removeAllViews();
            isRemoteViewUsed[index] = false;
        }
        remoteUserViewMap.remove(uid);

        RemoteStreamKey remoteStreamKey = new RemoteStreamKey(roomID, uid, StreamIndex.STREAM_INDEX_MAIN);
        VideoCanvas videoCanvas = new VideoCanvas();
        videoCanvas.renderView = null;
        videoCanvas.renderMode = VideoCanvas.RENDER_MODE_HIDDEN;
        rtcVideo.setRemoteVideoCanvas(remoteStreamKey, videoCanvas);

    }

    /**
     * 加入房间
     * @param roomId
     */
    private void joinRoom(String roomId) {

        rtcRoom = rtcVideo.createRTCRoom(roomId);
        rtcRoom.setRTCRoomEventHandler(rtcRoomEventHandler);
        String token = requestRoomToken(roomId);
        // 用户信息
        UserInfo userInfo = new UserInfo(localUid, "");
        // 设置房间配置
        boolean isAutoPublish = true;
        boolean isAutoSubscribeAudio = true;
        boolean isAutoSubscribeVideo = true;
        RTCRoomConfig roomConfig = new RTCRoomConfig(ChannelProfile.CHANNEL_PROFILE_CHAT_ROOM, isAutoPublish, isAutoSubscribeAudio, isAutoSubscribeVideo);
        // 加入房间
        rtcRoom.joinRoom(token, userInfo, roomConfig);
    }

    /**
     * 离开房间
     */
    private void leaveRoom() {
        if (rtcRoom != null) {
            rtcRoom.leaveRoom();
            rtcRoom.destroy();
            rtcRoom = null;
        }
    }

    IRTCRoomEventHandler rtcRoomEventHandler = new IRTCRoomEventHandler() {
        @Override
        public void onRoomStateChanged(String roomId, String uid, int state, String extraInfo) {
            super.onRoomStateChanged(roomId, uid, state, extraInfo);
            String info = String.format("roomId:%s, uid:%s, state:%d, extraInfo:%s", roomId, uid, state, extraInfo);
            ToastUtil.showLongToast(ByteBeautyActivity.this, info);
        }

        @Override
        public void onUserPublishStream(String uid, MediaStreamType type) {
            super.onUserPublishStream(uid, type);
            setRemoteRenderView(uid);
        }

        @Override
        public void onUserUnpublishStream(String uid, MediaStreamType type, StreamRemoveReason reason) {
            super.onUserUnpublishStream(uid, type, reason);
            removeRemoteView(uid);
        }

        @Override
        public void onLeaveRoom(RTCRoomStats stats) {
            super.onLeaveRoom(stats);
            ToastUtil.showLongToast(ByteBeautyActivity.this, "onLeaveRoom, stats:" + stats.toString());
        }

        @Override
        public void onUserJoined(UserInfo userInfo, int elapsed) {
            super.onUserJoined(userInfo, elapsed);
            ToastUtil.showLongToast(ByteBeautyActivity.this, "onUserJoined, uid:" + userInfo.getUid());
        }
    };

    /**
     * 引擎回调信息
     */
    IRTCVideoEventHandler videoEventHandler = new IRTCVideoEventHandler() {
    };

    /**
     * 初始化美颜相关资源
     */
    public void initEffect() {
        rtcVideoEffect = rtcVideo.getVideoEffectInterface();

        String licPath = effectResourceManager.getLicensePath();
        String modelPath = effectResourceManager.getModelPath();

        int res =  rtcVideoEffect.initCVResource(licPath,modelPath);
        Log.i(TAG, "initCVResource: " + res);


        int enableEffectRes = rtcVideoEffect.enableVideoEffect();
        Log.i(TAG, "enableVideoEffect: " + enableEffectRes);

        List<String> effectNodePaths = Arrays.asList(effectResourceManager.getBeautyPath(), effectResourceManager.getReshapePath());
        int effectNodesRes = rtcVideoEffect.setEffectNodes(effectNodePaths);
        Log.i(TAG, "setVideoEffectNodes: " + effectNodesRes);
    }

    /**
     * 修改美颜强度
     * @param key 美颜的键值
     * @param value 具体的值，取值范围[0, 1]，值越大越明显
     */
    public void onBeautyEffectChanged(String key, float value) {
        if (rtcVideoEffect == null) {
            return;
        }
        rtcVideoEffect.updateEffectNode(effectResourceManager.getBeautyPath(), key, value);
    }

    /**
     * 修改美形强度
     * @param key 美形的键值
     * @param value 具体的值，取值范围[0, 1]，值越大越明显
     */
    public void onReshapeEffectChanged(String key, float value) {
        if (rtcVideoEffect == null) {
            return;
        }
        rtcVideoEffect.updateEffectNode(effectResourceManager.getReshapePath(), key, value);
    }

    /**
     * 修改滤镜强度
     * @param key 滤镜名称
     * @param value 具体的值，取值范围[0, 1]，值越大越明显
     */
    public void onFilterEffectChanged(String key, float value) {
        if (rtcVideoEffect == null) {
            return;
        }
        rtcVideoEffect.setColorFilter(effectResourceManager.getFilterPathByName(key));
        rtcVideoEffect.setColorFilterIntensity(value);
    }

    /**
     * 修改贴纸
     * @param key 贴纸名称
     * @param selected 是否选中
     */
    public void onStickerEffectClicked(String key, boolean selected) {
        if (rtcVideoEffect == null) {
            return;
        }
        ArrayList<String> pathList = new ArrayList<>();
        pathList.add(effectResourceManager.getBeautyPath());
        pathList.add(effectResourceManager.getReshapePath());
        if (selected) {
            pathList.add(effectResourceManager.getStickerPathByName(key));
        }
        rtcVideoEffect.setEffectNodes(pathList);
    }

    /**
     * 使用背景分割功能
     * @param type 背景分割的类型
     * @param selected 是否选中
     */
    public void onVirtualEffectClicked(String type, boolean selected) {
        if (rtcVideoEffect == null) {
            return;
        }
        if (selected) {
            VirtualBackgroundSource backgroundSource = new VirtualBackgroundSource();
            if (TextUtils.equals(type, "color")) {
                backgroundSource.sourceType = VirtualBackgroundSourceType.COLOR;
                backgroundSource.sourceColor = Color.parseColor("#1278ff");
            } else if (TextUtils.equals(type, "image")) {
                backgroundSource.sourceType = VirtualBackgroundSourceType.IMAGE;
                backgroundSource.sourcePath = effectResourceManager.getExternalResourcePath() + File.separator + "virtual_background.png";
            } else {
                return;
            }

            String portraitPath = effectResourceManager.getEffectPortraitPath();
            rtcVideoEffect.enableVirtualBackground(portraitPath,backgroundSource);
        } else {
            rtcVideoEffect.disableVirtualBackground();
        }
    }

    private final EffectNode.EffectNodeCallback effectNodeCallback = new EffectNode.EffectNodeCallback() {
        @Override
        public void onEffectClicked(EffectNode effectNode) {
            if (rtcVideo == null) {
                Log.i("EffectNodeCallback", "onEffectClicked() : RTCVideo is null");
                return;
            }
            if (effectNode.type == EffectNode.EffectType.beauty) {
                if (TextUtils.equals(effectNode.path, "beauty")) {
                    onBeautyEffectChanged(effectNode.key, effectNode.value);
                } else if (TextUtils.equals(effectNode.path, "reshape")) {
                    onReshapeEffectChanged(effectNode.key, effectNode.value);
                }
            } else if (effectNode.type == EffectNode.EffectType.filter) {
                onFilterEffectChanged(effectNode.key, effectNode.value);
            } else if (effectNode.type == EffectNode.EffectType.sticker) {
                onStickerEffectClicked(effectNode.key, effectNode.selected);
            } else if (effectNode.type == EffectNode.EffectType.virtualBackground) {
                onVirtualEffectClicked(effectNode.key, effectNode.selected);
            } else {
                Log.i("EffectNodeCallback", "unknown EffectNode type");
            }
        }

        @Override
        public void onEffectValueChanged(EffectNode effectNode) {
            if (rtcVideo == null) {
                Log.i("EffectNodeCallback", "onEffectValueChanged() : RTCVideo is null");
                return;
            }
            if (effectNode.type == EffectNode.EffectType.beauty) {
                if (TextUtils.equals(effectNode.path, "beauty")) {
                    onBeautyEffectChanged(effectNode.key, effectNode.value);
                } else if (TextUtils.equals(effectNode.path, "reshape")) {
                    onReshapeEffectChanged(effectNode.key, effectNode.value);
                }
            } else if (effectNode.type == EffectNode.EffectType.filter) {
                onFilterEffectChanged(effectNode.key, effectNode.value);
            } else {
                Log.i("EffectNodeCallback", "invalid EffectNode type");
            }
        }
    };

    public EffectSection getBeautySection() {
        EffectSection beautySection = new EffectSection("美颜", true, null);

        EffectNode node0 = new EffectNode("美白", "whiten", EffectNode.EffectType.beauty, "beauty");
        EffectNode node1 = new EffectNode("磨皮", "smooth", EffectNode.EffectType.beauty, "beauty");
        EffectNode node2 = new EffectNode("大眼", "Internal_Deform_Eye", EffectNode.EffectType.beauty, "reshape");
        EffectNode node3 = new EffectNode("瘦脸", "Internal_Deform_Overall", EffectNode.EffectType.beauty, "reshape");
        node0.selected = true;
        beautySection.effectNodes = Arrays.asList(node0, node1, node2, node3);
        return beautySection;
    }

    public EffectSection getStickerSection() {
        EffectSection stickerSection = new EffectSection("贴纸", false, null);
        EffectNode node0 = new EffectNode("黑猫眼镜", "stickers_heimaoyanjing", EffectNode.EffectType.sticker);
        EffectNode node1 = new EffectNode("招财猫", "stickers_zhaocaimao", EffectNode.EffectType.sticker);
        EffectNode node2 = new EffectNode("缺爱熊", "stickers_kejiganqueaixiong", EffectNode.EffectType.sticker);
        EffectNode node3 = new EffectNode("魔法宝石", "stickers_mofabaoshi", EffectNode.EffectType.sticker);
        EffectNode node4 = new EffectNode("龙卷风", "aidelongjuanfeng", EffectNode.EffectType.sticker);
        EffectNode node5 = new EffectNode("美猴王", "meihouwang", EffectNode.EffectType.sticker);
        EffectNode node6 = new EffectNode("漫画脸", "manhualian", EffectNode.EffectType.sticker);
        EffectNode node7 = new EffectNode("猪可爱", "animoji_keaizhu", EffectNode.EffectType.sticker);
        stickerSection.effectNodes =  Arrays.asList(node0, node1, node2, node3, node4, node5, node6, node7);
        return stickerSection;
    }

    public EffectSection getFilterSection() {
        EffectSection filterSection = new EffectSection("滤镜", true, null);
        EffectNode node0 = new EffectNode("蜜桃", "Filter_06_03", EffectNode.EffectType.filter);
        EffectNode node1 = new EffectNode("清透", "Filter_37_L5", EffectNode.EffectType.filter);
        EffectNode node2 = new EffectNode("夜色", "Filter_35_L3", EffectNode.EffectType.filter);
        EffectNode node3 = new EffectNode("冷氧", "Filter_30_Po8", EffectNode.EffectType.filter);

        node0.selected = true;
        filterSection.effectNodes =  Arrays.asList(node0, node1, node2, node3);
        return filterSection;
    }

    public EffectSection getVirtualBackgroundSection() {
        EffectSection virtualBackgroundSection = new EffectSection("背景分割", false, null);
        EffectNode node0 = new EffectNode("纯色", "color", EffectNode.EffectType.virtualBackground);
        EffectNode node1 = new EffectNode("图片", "image", EffectNode.EffectType.virtualBackground);
        virtualBackgroundSection.effectNodes = Arrays.asList(node0, node1);
        return virtualBackgroundSection;
    }


    @Override
    protected void onDestroy() {
        super.onDestroy();
        leaveRoom();
        if (rtcRoom != null) {
            rtcRoom.destroy();
            rtcRoom = null;
        }
        if (rtcVideo != null) {
            rtcVideo.stopAudioCapture();
            rtcVideo.stopVideoCapture();
        }
        RTCVideo.destroyRTCVideo();
    }
}