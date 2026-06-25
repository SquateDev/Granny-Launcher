package dev.squatedev.akironlauncher;

import android.os.Bundle;
import android.os.Handler;
import android.view.View;

import dev.squatedev.akironlauncher.API.LocalPlayer;
import dev.squatedev.akironlauncher.Activity.GUI;
import dev.squatedev.akironlauncher.Activity.ModMenu;

public class Launcher extends com.unity3d.player.UnityPlayerActivity {
    private boolean menu = false;
    @Override
    protected void onCreate(Bundle bundle){
        super.onCreate(bundle);
        getWindow().getDecorView().setSystemUiVisibility(View.SYSTEM_UI_FLAG_HIDE_NAVIGATION | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY);
        Handler handler = new Handler();
        Runnable runnable = new Runnable() {
            @Override
            public void run() {
                try {
                    if (getWindow().getDecorView() != null) {
                        GUI.GUI(getApplicationContext(), getWindow().getDecorView(), v -> {
                           menu = !menu;
                           if(menu){
                               ModMenu.init(getApplicationContext(), getWindow().getDecorView());
                           } else {
                               ModMenu.closeMenu();
                           }
                        });
                    }
                } catch (RuntimeException e) {
                    throw new RuntimeException(e);
                }
            }
        };
        handler.postDelayed(runnable, 500);
    }
}
