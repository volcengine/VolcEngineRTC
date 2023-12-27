package com.faceunity.nama.dialog;

import android.content.Context;
import android.content.res.Resources;
import android.util.TypedValue;
import android.view.Gravity;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.StringRes;

import com.faceunity.nama.R;

import java.lang.ref.WeakReference;


/**
 * Created by tujh on 2018/6/28.
 */
public final class ToastHelper {
    private static Toast sNormalToast;
    private static Toast sWhiteTextToast;
    private static WeakReference<Context> mWeakContext;

    public static void showToast(Context context, String str) {
        Toast toast = Toast.makeText(context, str, Toast.LENGTH_SHORT);
        toast.setGravity(Gravity.CENTER, 0, 0);
        toast.show();
    }

    public static void showToast(Context context, @StringRes int strId) {
        showToast(context, context.getString(strId));
    }

    public static void showWhiteTextToast(Context context, @StringRes int strId) {
        showWhiteTextToast(context, context.getString(strId));
    }

    public static void showNormalToast(Context context, @StringRes int strId) {
        showNormalToast(context, context.getString(strId));
    }

    public static void dismissToast() {
        dismissWhiteTextToast();
        dismissNormalToast();
    }


    public static void dismissWhiteTextToast() {
        if (sWhiteTextToast != null) {
            sWhiteTextToast.cancel();
        }
    }


    public static void dismissNormalToast() {
        if (sNormalToast != null) {
            sNormalToast.cancel();
        }
    }


    public static void showWhiteTextToast(Context context, String text) {
        if (mWeakContext != null && mWeakContext.get() == context && sWhiteTextToast != null) {
            TextView view = (TextView) sWhiteTextToast.getView();
            view.setText(text);
            if (!view.isShown()) {
                sWhiteTextToast.show();
            }
            return;
        }
        mWeakContext = new WeakReference<>(context);
        Resources resources = context.getResources();
        TextView textView = new TextView(context);
        textView.setTextColor(resources.getColor(R.color.colorWhite));
        textView.setGravity(Gravity.CENTER);
        textView.setTextSize(TypedValue.COMPLEX_UNIT_PX, resources.getDimension(R.dimen.x64));
        textView.setText(text);
        sWhiteTextToast = new Toast(context);
        sWhiteTextToast.setView(textView);
        sWhiteTextToast.setDuration(Toast.LENGTH_SHORT);
        int yOffset = context.getResources().getDimensionPixelSize(R.dimen.x560);
        sWhiteTextToast.setGravity(Gravity.CENTER_HORIZONTAL | Gravity.TOP, 0, yOffset);
        sWhiteTextToast.show();
    }


    public static void showNormalToast(Context context, String text) {
        if (mWeakContext != null && mWeakContext.get() == context && sNormalToast != null) {
            TextView view = (TextView) sNormalToast.getView();
            view.setText(text);
            if (!view.isShown()) {
                sNormalToast.show();
            }
            return;
        }
        mWeakContext = new WeakReference<>(context);
        Resources resources = context.getResources();
        TextView textView = new TextView(context);
        textView.setTextColor(resources.getColor(R.color.colorWhite));
        textView.setGravity(Gravity.CENTER);
        textView.setTextSize(TypedValue.COMPLEX_UNIT_PX, resources.getDimension(R.dimen.x26));
        textView.setBackgroundResource(R.drawable.bg_toast_more);
        int hPadding = resources.getDimensionPixelSize(R.dimen.x28);
        int vPadding = resources.getDimensionPixelSize(R.dimen.x16);
        textView.setPadding(hPadding, vPadding, hPadding, vPadding);
        textView.setText(text);
        sNormalToast = new Toast(context);
        sNormalToast.setView(textView);
        sNormalToast.setDuration(Toast.LENGTH_SHORT);
        int yOffset = context.getResources().getDimensionPixelSize(R.dimen.x182);
        sNormalToast.setGravity(Gravity.CENTER_HORIZONTAL | Gravity.TOP, 0, yOffset);
        sNormalToast.show();
    }

}
