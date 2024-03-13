package rtc.volcengine.apiexample;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.DefaultItemAnimator;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.text.TextUtils;
import android.widget.TextView;

import com.ss.bytertc.engine.RTCVideo;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import rtc.volcengine.apiexample.common.adapter.ExampleListAdapter;
import rtc.volcengine.apiexample.common.annotations.ApiExample;
import rtc.volcengine.apiexample.common.data.ExampleInfo;

public class MainActivity extends BaseActivity {

    private RecyclerView exampleListRv;

    private List<ExampleInfo> exampleList = new ArrayList<>();
    ExampleListAdapter exampleAdapter = new ExampleListAdapter();


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        exampleListRv = findViewById(R.id.api_list);

        exampleListRv.setLayoutManager(new LinearLayoutManager(this, LinearLayoutManager.VERTICAL, false));
        exampleListRv.setAdapter(exampleAdapter);
        exampleListRv.setItemAnimator(new DefaultItemAnimator());
        exampleAdapter.setOnItemClickListener((v, pos) -> {
            if (pos >= 0 && pos < exampleList.size()) {
                Class targetClazz = exampleList.get(pos).getAction();
                startActivity(new Intent(MainActivity.this, targetClazz));
            }
        });
        buildExampleList();
        requestPermission();

        ((TextView)findViewById(R.id.version)).setText("sdk 版本: " + RTCVideo.getSDKVersion());
    }


    private void buildExampleList() {
        try {
            ActivityInfo[] activityInfos = getPackageManager().getPackageInfo(getPackageName(), PackageManager.GET_ACTIVITIES).activities;
            if (activityInfos != null) {
                for (ActivityInfo activityInfo : activityInfos) {
                    Class<?> activityClass = Class.forName(activityInfo.name);
                    if (activityClass.isAnnotationPresent(ApiExample.class)) {
                        ApiExample apiExample = activityClass.getAnnotation(ApiExample.class);
                        String category = apiExample.category();
                        String name = apiExample.name();
                        double order = apiExample.order();
                        ExampleInfo info = new ExampleInfo(name, activityClass, order);
                        if (!TextUtils.isEmpty(category)) {
                            info.setCategory(category);
                        }
                        exampleList.add(info);
                    }
                }
            }
            Collections.sort(exampleList, (o1, o2) -> Double.compare(o1.getOrder(), o2.getOrder()));
        } catch (PackageManager.NameNotFoundException | ClassNotFoundException e) {
            e.printStackTrace();
        }
        exampleAdapter.setExampleList(exampleList);
    }

}