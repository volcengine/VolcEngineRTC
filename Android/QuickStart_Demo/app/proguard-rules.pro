# Add project specific ProGuard rules here.
# You can control the set of applied configuration files using the
# proguardFiles setting in build.gradle.
#
# For more details, see
#   http://developer.android.com/guide/developing/tools/proguard.html

# If your project uses WebView with JS, uncomment the following
# and specify the fully qualified class name to the JavaScript interface
# class:
#-keepclassmembers class fqcn.of.javascript.interface.for.webview {
#   public *;
#}

# Uncomment this to preserve the line number information for
# debugging stack traces.
#-keepattributes SourceFile,LineNumberTable

# If you keep the line number information, uncomment this to
# hide the original source file name.
#-renamesourcefileattribute SourceFile

-keepclasseswithmembernames class * {
    native <methods>;
}


##保证CalledByNative不被混淆
-keep @org.webrtc.CalledByNative class *

#保持webrtc、RtcEngine中的类不被混淆
-keep class org.webrtc.**{*;}
-keep class com.bytedance.services.** {*;}
-keep class com.bytedance.webrtc.** {*;}
-keep class com.bytedance.realx.** {*;}
-keep class com.bytedance.bae.** {*;}
-keep class com.ss.bytertc.**{*;}



#保证所有带有带有CallByNaitve注解方法与类名称不被混淆
-keepclasseswithmembers class * {
    @org.webrtc.CalledByNative *;
}
-keepclasseswithmembers class * {
    @com.bytedance.bae.base.CalledByNative *;
}

-keepattributes Signature
-keepattributes *Annotation*


