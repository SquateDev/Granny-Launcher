# Keep SafeDK classes
-keep class com.safedk.android.** { *; }
-dontwarn com.safedk.android.**
-keepattributes *Annotation*

# Alternative: Keep just the specific missing class
-keep class com.safedk.android.utils.annotations.AdNetworkIdentifier
-dontwarn com.safedk.android.utils.annotations.AdNetworkIdentifier