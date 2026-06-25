package dev.squatedev.akironlauncher.Activity;

import android.app.Activity;
import android.content.Context;
import android.graphics.Color;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.ImageView;
import android.widget.PopupWindow;
import android.widget.TextView;
import android.widget.ViewFlipper;

import dev.squatedev.akironlauncher.R;

public class ModMenu extends Activity {
    private static Context contextAPP;
    private static PopupWindow popupWindow;
    private static int color_on = Color.parseColor("#B2EBF2");
    private static int color_off = Color.parseColor("#E2E2E2");
    private static View pop_menu_view;
    private static int chossen = 1;
    private static ViewFlipper flipper_menu;

    /* ------- ID CATEGORY PLAYER ------- */
    private static ImageView img_player;
    private static TextView text_player;

    /* ------- ID CATEGORY RENDER ------- */
    private static ImageView img_render;
    private static TextView text_render;

    /* ------- ID CATEGORY POINTER ------- */
    private static ImageView img_pointer;
    private static TextView text_pointer;

    /* ------- ID CATEGORY LANGUAGE ------- */
    private static ImageView img_language;
    private static TextView text_language;

    private static View getFindCommponent(int id){
        return pop_menu_view.findViewById(id);
    }

    private static void buffer_color_clear(){
        img_player.setColorFilter(color_off);
        img_render.setColorFilter(color_off);
        img_pointer.setColorFilter(color_off);
        img_language.setColorFilter(color_off);
        text_player.setTextColor(color_off);
        text_render.setTextColor(color_off);
        text_pointer.setTextColor(color_off);
        text_language.setTextColor(color_off);
    }

    private static void chossen(int chossen){
        flipper_menu.setDisplayedChild(chossen - 1);
        switch (chossen){
            case 1:
                buffer_color_clear();
                img_player.setColorFilter(color_on);
                text_player.setTextColor(color_on);
                break;
            case 2:
                buffer_color_clear();
                img_render.setColorFilter(color_on);
                text_render.setTextColor(color_on);
                break;
            case 3:
                buffer_color_clear();
                img_pointer.setColorFilter(color_on);
                text_pointer.setTextColor(color_on);
                break;
            case 4:
                buffer_color_clear();
                img_language.setColorFilter(color_on);
                text_language.setTextColor(color_on);
                break;
        }
    }

    private static void init_category_linstener(){
        /*--------- ImageView ----------*/
        img_player = (ImageView) getFindCommponent(R.id.image_player);
        img_render = (ImageView) getFindCommponent(R.id.image_render);
        img_pointer = (ImageView) getFindCommponent(R.id.image_pointer);
        img_language = (ImageView) getFindCommponent(R.id.image_language);

        /*---------- TextView --------- */
        text_player =  (TextView) getFindCommponent(R.id.text_player);
        text_render =  (TextView) getFindCommponent(R.id.text_render);
        text_pointer =  (TextView) getFindCommponent(R.id.text_pointer);
        text_language =  (TextView) getFindCommponent(R.id.text_language);

        /*--------- ViewFlipper ------- */
        flipper_menu = (ViewFlipper) getFindCommponent(R.id.mod_flipper);

        View.OnClickListener click_player = view -> {
            chossen = 1;
            chossen(chossen);
        };

        View.OnClickListener click_render = view -> {
            chossen = 2;
            chossen(chossen);
        };

        View.OnClickListener click_pointer = view -> {
            chossen = 3;
            chossen(chossen);
        };

        View.OnClickListener click_language = view -> {
            chossen = 4;
            chossen(chossen);
        };
        // Player CLICK
        img_player.setOnClickListener(click_player);
        text_player.setOnClickListener(click_player);
        // Render CLICK
        img_render.setOnClickListener(click_render);
        text_render.setOnClickListener(click_render);
        // Pointer CLICK
        img_pointer.setOnClickListener(click_pointer);
        text_pointer.setOnClickListener(click_pointer);
        // LANGUAGE Click
        img_language.setOnClickListener(click_language);
        text_language.setOnClickListener(click_language);
    }

    public static void init(Context context, View root){
        contextAPP = context;

        LayoutInflater layoutInflater = (LayoutInflater) context.getSystemService(LAYOUT_INFLATER_SERVICE);
        View pop = layoutInflater.inflate(R.layout.modmenu, null);
        pop_menu_view = pop;
        init_category_linstener();
        chossen(chossen);
        PlayerCategory.init_click_function(pop);

        popupWindow = new PopupWindow(pop, dips(360), dips(295));
        popupWindow.showAtLocation(root, Gravity.CENTER | Gravity.CENTER, 0, 0);
    }

    public static void closeMenu(){
        if(popupWindow != null || popupWindow.isShowing()){
            popupWindow.dismiss();
        }
    }

    private static int dips(int value) {
        return Math.round(value * contextAPP.getResources().getDisplayMetrics().scaledDensity);
    }
}
