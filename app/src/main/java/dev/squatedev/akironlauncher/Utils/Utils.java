package dev.squatedev.akironlauncher.Utils;

import android.annotation.TargetApi;
import android.app.Activity;
import android.content.*;
import android.content.pm.*;
import android.os.*;
import android.text.TextUtils;
import android.util.*;

import com.ironsource.C;

import java.io.*;
import java.lang.reflect.Method;
import java.nio.ByteBuffer;
import java.util.*;
import java.util.zip.*;

import dalvik.system.DexClassLoader;
import dalvik.system.InMemoryDexClassLoader;

public class Utils extends Activity {
    private static Utils instance;
    Context contextAPP;
    Context context;
    String tag = "Akiron";

    private Utils (Context context){
        if(this.context == null) this.context = context;
    }

    public static Utils getInstance(Context context) {
        if(instance == null){
            instance = new Utils(context);
        }
        return instance;
    }

    public int getScaled(int base){
        DisplayMetrics matrics = context.getResources().getDisplayMetrics();
        float screenDP =  matrics.widthPixels / matrics.density;
        float scaleFactor = screenDP / 360;
        scaleFactor = Math.max(1.2f, Math.min(2.0f, scaleFactor));
        return Math.round(base * scaleFactor);
    }

    public void log_error(String e) {
        Log.e(tag, e);
    }
    public void log_info(String i) {
        Log.i(tag, i);
    }
    public void log_debug(String d) {
        Log.d(tag, d);
    }

}