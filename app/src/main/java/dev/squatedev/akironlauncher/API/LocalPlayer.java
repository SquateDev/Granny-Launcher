package dev.squatedev.akironlauncher.API;

public class LocalPlayer {
    public static native String getPosText();
    public static native void setPos(float x, float y, float z);
    public static native void setGodMode(boolean godmode, boolean granny, boolean momspider, boolean spider, boolean falldamage);
    public static native boolean getGame();

    // Enemy Clone
    public static native void incressGranny();
    public static native void deincressGranny();
    public static native void incressMom();
    public static native void deincressMom();



}
