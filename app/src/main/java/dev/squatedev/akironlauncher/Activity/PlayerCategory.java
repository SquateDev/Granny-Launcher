package dev.squatedev.akironlauncher.Activity;

import android.view.View;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.Switch;
import android.widget.TextView;

import org.w3c.dom.Text;

import dev.squatedev.akironlauncher.API.LocalPlayer;
import dev.squatedev.akironlauncher.R;

public class PlayerCategory {
    private static View pop_menu_view;

    // GodMode Element
    private static LinearLayout godmode_linear;
    private static LinearLayout godmode_setting;
    private static LinearLayout godmode_granny_linear;
    private static LinearLayout godmode_momspider_linear;


    // GodMode Tumbler
    private static ImageView godmode_info;
    private static Switch godmode_switch;
    private static Switch granny_mode_switch;
    private static Switch momspider_mode_switch;


    // Granny clone btn
    private static TextView btn_plus;
    private static TextView text_cout;
    private static TextView btn_minus;
    private static int cout_granny = 0;

    // MomSpider Clone
    private static TextView spider_plus;
    private static TextView spider_cout;
    private static TextView spider_minus;
    private static int cout_momspider;



    // GodMode Function
    private static boolean godmode = false; // mai function boolean
     private static boolean godmode_setting_bool = false;
     private static boolean granny_mode = true; // Granny GodMode
     private static boolean momspider_mode = true; // MomSpider GodMode
     private static boolean spider_mode = true; // Spider GodMode
     private static boolean fall_mode = true; // Falling GodMode


    private static View getFindCommponent(int id){
        return pop_menu_view.findViewById(id);
    }

    private static void restart(){
        godmode_setting_bool = false;
        granny_mode_switch.setChecked(granny_mode);
        momspider_mode_switch.setChecked(momspider_mode);
        godmode_switch.setChecked(godmode);
        text_cout.setText(""+cout_granny);
        spider_cout.setText(""+cout_momspider);
    }


    private static void init_id(){
        btn_plus = (TextView) getFindCommponent(R.id.granny_plus);
        btn_minus = (TextView) getFindCommponent(R.id.granny_minus);
        text_cout = (TextView) getFindCommponent(R.id.count_granny);

        spider_plus = (TextView)getFindCommponent(R.id.spider_plus);
        spider_cout = (TextView)getFindCommponent(R.id.count_spider);
        spider_minus = (TextView)getFindCommponent(R.id.spider_minus);


        godmode_linear = (LinearLayout) getFindCommponent(R.id.module_godmode);
        godmode_info = (ImageView) getFindCommponent(R.id.info_godmode);
        godmode_switch = (Switch) getFindCommponent(R.id.switch_godmode);
        godmode_switch = (Switch) getFindCommponent(R.id.switch_godmode);
        godmode_setting = (LinearLayout) getFindCommponent(R.id.setting_godmode);
        godmode_granny_linear = (LinearLayout) getFindCommponent(R.id.linear_setting_godmode_granny);
        granny_mode_switch = (Switch) getFindCommponent(R.id.switch_granny_mode);
        godmode_momspider_linear = (LinearLayout) getFindCommponent(R.id.linear_setting_godmode_momspider);
        momspider_mode_switch = (Switch) getFindCommponent(R.id.switch_momspider);
    }

    private static void set_godmode_linstener(){
        // Function Granny GodMode
        godmode_linear.setOnClickListener(v -> {
            godmode = !godmode;
            godmode_switch.setChecked(godmode);
            LocalPlayer.setGodMode(godmode, granny_mode, momspider_mode, spider_mode, fall_mode);
        });
        godmode_info.setOnClickListener(view -> {
            godmode_setting_bool = !godmode_setting_bool;
            if(godmode_setting_bool){
                godmode_setting.setVisibility(View.VISIBLE);
            } else {
                godmode_setting.setVisibility(View.GONE);
            }
        });
        godmode_switch.setOnClickListener(v -> {
            godmode = !godmode;
            godmode_switch.setChecked(godmode);
            LocalPlayer.setGodMode(godmode, granny_mode, momspider_mode, spider_mode, fall_mode);
        });

        // Setting granny GodMode callback
        godmode_granny_linear.setOnClickListener(view -> {
            granny_mode = !granny_mode;
            granny_mode_switch.setChecked(granny_mode);
            LocalPlayer.setGodMode(godmode, granny_mode, momspider_mode, spider_mode, fall_mode);
        });
        granny_mode_switch.setOnClickListener(view -> {
            granny_mode = !granny_mode;
            granny_mode_switch.setChecked(granny_mode);
            LocalPlayer.setGodMode(godmode, granny_mode, momspider_mode, spider_mode, fall_mode);
        });

        // Mode MomSpider GodMode
        godmode_momspider_linear.setOnClickListener(view -> {
            momspider_mode = !momspider_mode;
            momspider_mode_switch.setChecked(momspider_mode);
            LocalPlayer.setGodMode(godmode, granny_mode, momspider_mode, spider_mode, fall_mode);
        });
        momspider_mode_switch.setOnClickListener(view -> {
            momspider_mode = !momspider_mode;
            momspider_mode_switch.setChecked(momspider_mode);
            LocalPlayer.setGodMode(godmode, granny_mode, momspider_mode, spider_mode, fall_mode);

        });
        restart();
    }

    private static void set_granny_clone(){
        btn_plus.setOnClickListener(v -> {
            if(cout_granny < 50 && LocalPlayer.getGame()){
                cout_granny++;
                text_cout.setText(""+cout_granny);
                LocalPlayer.incressGranny();
            }
        });
        btn_minus.setOnClickListener(v -> {
            if(cout_granny > 0 && LocalPlayer.getGame()){
                cout_granny--;
                text_cout.setText(""+cout_granny);
                LocalPlayer.deincressGranny();
            }
        });
    }

    private static void set_momspider_clone(){
        spider_plus.setOnClickListener(v -> {
            if(cout_momspider < 50 && LocalPlayer.getGame()){
                cout_momspider++;
                spider_cout.setText(""+cout_momspider);
                LocalPlayer.incressMom();
            }
        });
        spider_minus.setOnClickListener(v -> {
            if(cout_momspider > 0 && LocalPlayer.getGame()){
                cout_momspider--;
                spider_cout.setText(""+cout_momspider);
                LocalPlayer.deincressMom();
            }
        });

    }

    public static void init_click_function(View view){
        pop_menu_view = view;
        init_id();
        set_godmode_linstener();
        set_granny_clone();
        set_momspider_clone();
    }
}
