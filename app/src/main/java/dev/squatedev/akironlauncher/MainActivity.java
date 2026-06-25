package dev.squatedev.akironlauncher;

import android.app.Activity;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.graphics.Color;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Looper;
import android.provider.Settings;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import com.unity3d.player.UnityPlayerActivity;

import dev.squatedev.akironlauncher.Activity.Loader;

public class MainActivity extends Activity {
    static {
        System.loadLibrary("akironlauncher");
    }
    private TextView textView;
    private Loader loader;
    private Handler mainHandler = new Handler(Looper.getMainLooper());
    private static native void setNativeLoad(String path);
    private static native void loadHook();

    @Override
    protected void onCreate(Bundle bundle) {
        super.onCreate(bundle);
        loader = Loader.getInstance(this);
        textView = new TextView(getApplicationContext());
        textView.setTextColor(Color.CYAN);
        textView.setLayoutParams(new LinearLayout.LayoutParams(-1, -1));
        textView.setGravity(Gravity.CENTER | Gravity.CENTER_VERTICAL);
        setContentView(textView);
        requestStorageAccess();
    }

    private void requestStorageAccess() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.R) {
            if (!Environment.isExternalStorageManager()) {
                Intent intent = new Intent(Settings.ACTION_MANAGE_APP_ALL_FILES_ACCESS_PERMISSION);
                intent.setData(Uri.parse("package:" + getPackageName()));
                startActivity(intent);
            } else {
                startCopying();
            }
        } else if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            if (checkSelfPermission(android.Manifest.permission.READ_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED) {
                requestPermissions(new String[]{
                        android.Manifest.permission.READ_EXTERNAL_STORAGE,
                        android.Manifest.permission.WRITE_EXTERNAL_STORAGE
                }, 1);
            } else {
                startCopying();
            }
        } else {
            startCopying();
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        if (requestCode == 1) {
            startCopying();
        }
    }

    @Override
    protected void onResume() {
        super.onResume();
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.R) {
            if (Environment.isExternalStorageManager()) {
                startCopying();
            }
        }
    }

    private void startCopying() {
        textView.setText("Starting copy...");
        loader.copyAndLoad("com.dvloper.granny", new Loader.LoadCallback() {
            @Override
            public void onDone(String apkPath, String assetsPath) {
                String newPrefix = getFilesDir().getAbsolutePath();
                setNativeLoad(newPrefix);
                mainHandler.post(() -> {
                    textView.setText("Launching game...");
                    try {
                        Thread.sleep(500);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                    start_launch();
                });
            }

            @Override
            public void onError(String error) {
                mainHandler.post(() -> textView.setText("Copy error: " + error));
            }

            @Override
            public void onProgress(String fileName, int current, int total) {
                mainHandler.post(() -> textView.setText("[" + current + "/" + total + "] \n" + fileName));
            }
        });
    }

    private void start_launch() {
        Intent intent = new Intent(this, Launcher.class);
        startActivity(intent);
        Handler handler = new Handler();
        Runnable runnable = new Runnable() {
            @Override
            public void run() {
                loadHook();
            }
        };
        handler.postDelayed(runnable, 4000);
    }
}