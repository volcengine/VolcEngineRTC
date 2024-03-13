package rtc.volcengine.apiexample.common.data;

import android.app.Activity;

public class ExampleInfo {

    private String category;
    private String exampleName;
    private Class<Activity> action;
    private double order;

    public ExampleInfo(String exampleName, Class action, double order) {
        this.action = action;
        this.exampleName = exampleName;
        this.order = order;
    }

    public Class getAction() {
        return action;
    }

    public double getOrder() {
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
