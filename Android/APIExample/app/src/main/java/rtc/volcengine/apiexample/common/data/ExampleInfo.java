package rtc.volcengine.apiexample.common.data;

import android.app.Activity;

public class ExampleInfo {

    private String category;
    private String exampleName;
    private Class<Activity> action;
    private int order;

    public ExampleInfo(String exampleName, Class action, int order) {
        this.action = action;
        this.exampleName = exampleName;
        this.order = order;
    }

    public Class getAction() {
        return action;
    }

    public int getOrder() {
        return order;
    }

    public String getCategory() {
        return category;
    }

    public String getExampleName() {
        return exampleName;
    }

    public void setCategory(String category) {
        this.category = category;
    }
}
