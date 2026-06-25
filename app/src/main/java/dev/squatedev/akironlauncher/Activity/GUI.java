package dev.squatedev.akironlauncher.Activity;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Context;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.PopupWindow;
import androidx.annotation.NonNull;
import dev.squatedev.akironlauncher.R;
public class GUI extends Activity {
    @SuppressLint("MissingInflatedId")
    public static void GUI(@NonNull Context context, View view, View.OnClickListener onClickListener){
        LayoutInflater layoutInflater = (LayoutInflater) context.getSystemService(LAYOUT_INFLATER_SERVICE);
        View pop = layoutInflater.inflate(R.layout.gui, null);

        LinearLayout layout = pop.findViewById(R.id.gui_id);
        layout.setOnClickListener(onClickListener);

        PopupWindow gui = new PopupWindow(pop, -2, -2);
        gui.showAtLocation(view, Gravity.TOP | Gravity.LEFT, 20, 40);
    }
}
