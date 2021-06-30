package com.ss.video.rtc.demo.meetingrtcdemo.common;

import android.annotation.TargetApi;
import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Intent;
import android.os.Build;
import android.os.IBinder;

import androidx.annotation.Nullable;
import androidx.core.app.NotificationCompat;

import com.ss.video.rtc.demo.meetingrtcdemo.R;
import com.ss.video.rtc.demo.meetingrtcdemo.feature.room.RoomActivity;


@TargetApi(Build.VERSION_CODES.JELLY_BEAN_MR1)
public class MoiraeService extends Service {

    public static final String CHANNEL_ID = "MoiraeServiceChannel";

    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public void onCreate() {
        super.onCreate();
        startAsForeground(new Intent());
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        startAsForeground(intent);
        return START_NOT_STICKY;
    }

    private void startAsForeground(Intent intent) {
        String input = intent.getStringExtra("inputExtra");
        createNotificationChannel();
        Intent notificationIntent = new Intent(this, RoomActivity.class);
        PendingIntent pendingIntent = PendingIntent.getActivity(this,
                0, notificationIntent, 0);

        Notification notification = new NotificationCompat.Builder(this, CHANNEL_ID)
                .setContentTitle("视频通话正在后台运行")
                .setContentText(input)
                .setSmallIcon(R.drawable.app_logo)
                .setContentIntent(pendingIntent)
                .build();

        startForeground(1, notification);
    }

    private void createNotificationChannel() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            NotificationChannel serviceChannel = new NotificationChannel(
                    CHANNEL_ID,
                    "Foreground Service Channel",
                    NotificationManager.IMPORTANCE_DEFAULT
            );

            NotificationManager manager = getSystemService(NotificationManager.class);
            if (manager != null) {
                manager.createNotificationChannel(serviceChannel);
            }
        }
    }
}
