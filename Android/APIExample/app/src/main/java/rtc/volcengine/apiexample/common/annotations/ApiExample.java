package rtc.volcengine.apiexample.common.annotations;

import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

@Retention(RetentionPolicy.RUNTIME)
public @interface ApiExample {
    int order();
    String category() default "";

    String name();
}