package dev.squatedev.akironlauncher.Activity;

import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.util.Log;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.util.Enumeration;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

public class Loader {
    private Context context;
    private static Loader instance;
    private static final String TAG = "CopyAPP";

    private Loader(Context ctx) {
        this.context = ctx;
    }

    public static Loader getInstance(Context ctx) {
        if (instance == null) {
            instance = new Loader(ctx);
        }
        return instance;
    }

    public interface LoadCallback {
        void onDone(String apkPath, String assetsPath);
        void onError(String error);
        void onProgress(String fileName, int current, int total);
    }

    public void copyAndLoad(String packageName, LoadCallback callback) {
        new Thread(() -> {
            try {
                ApplicationInfo appInfo = context.getPackageManager().getApplicationInfo(packageName, 0);
                String dataDir = context.getFilesDir().getAbsolutePath();
                String destApk = dataDir + "/base.apk";
                String assetsPath = dataDir + "/assets";

                File destApkFile = new File(destApk);
                File assetsFolder = new File(assetsPath);

                Log.d(TAG, "Source APK: " + appInfo.sourceDir);
                Log.d(TAG, "Dest APK: " + destApk);
                Log.d(TAG, "Assets dir: " + assetsPath);

                if (!destApkFile.exists() || !assetsFolder.exists() || assetsFolder.listFiles().length == 0) {
                    Log.d(TAG, "Need copy, starting...");

                    if (destApkFile.exists()) destApkFile.delete();
                    if (assetsFolder.exists()) deleteDir(assetsFolder);
                    assetsFolder.mkdirs();

                    copyFile(appInfo.sourceDir, destApk);
                    destApkFile.setReadOnly();

                    extractAssets(destApk, assetsPath, callback);

                    logDirectoryStructure(assetsPath);
                } else {
                    Log.d(TAG, "Files already exist, skipping copy");
                    logDirectoryStructure(assetsPath);
                }

                callback.onDone(destApk, assetsPath);

            } catch (Exception e) {
                Log.e(TAG, "Error: " + e.getMessage(), e);
                callback.onError(e.getMessage());
            }
        }).start();
    }

    private void copyFile(String source, String dest) throws Exception {
        FileInputStream fis = null;
        FileOutputStream fos = null;
        try {
            fis = new FileInputStream(source);
            fos = new FileOutputStream(dest);
            byte[] buffer = new byte[8192];
            int length;
            long total = 0;
            while ((length = fis.read(buffer)) > 0) {
                fos.write(buffer, 0, length);
                total += length;
            }
            fos.flush();
            Log.d(TAG, "Copied " + total + " bytes");
        } finally {
            if (fis != null) fis.close();
            if (fos != null) fos.close();
        }
    }

    private void extractAssets(String apkPath, String destDir, LoadCallback callback) throws Exception {
        Log.d(TAG, "Extracting assets from: " + apkPath);

        ZipFile zip = new ZipFile(apkPath);
        Enumeration<? extends ZipEntry> entries = zip.entries();

        int total = 0;
        int current = 0;

        java.util.ArrayList<ZipEntry> assetEntries = new java.util.ArrayList<>();

        while (entries.hasMoreElements()) {
            ZipEntry entry = entries.nextElement();
            String name = entry.getName();
            if (!entry.isDirectory() && name.startsWith("assets/") && !name.contains("lib/") && !name.endsWith(".so")) {
                assetEntries.add(entry);
                Log.d(TAG, "Found asset: " + name);
            }
        }

        total = assetEntries.size();
        Log.d(TAG, "Total assets to extract: " + total);

        for (ZipEntry entry : assetEntries) {
            current++;
            String name = entry.getName();
            String relativePath = name.substring("assets/".length());
            String destPath = destDir + "/" + relativePath;
            File destFile = new File(destPath);

            File parentDir = destFile.getParentFile();
            if (parentDir != null && !parentDir.exists()) {
                parentDir.mkdirs();
            }

            InputStream is = null;
            FileOutputStream fos = null;
            try {
                is = zip.getInputStream(entry);
                fos = new FileOutputStream(destFile);
                byte[] buf = new byte[8192];
                int len;
                while ((len = is.read(buf)) > 0) {
                    fos.write(buf, 0, len);
                }
                fos.flush();
                Log.d(TAG, "Extracted [" + current + "/" + total + "]: " + relativePath);
            } finally {
                if (is != null) is.close();
                if (fos != null) fos.close();
            }

            callback.onProgress(relativePath, current, total);
        }

        zip.close();
        Log.d(TAG, "Extraction complete");
    }

    private void logDirectoryStructure(String path) {
        File dir = new File(path);
        if (dir.exists() && dir.isDirectory()) {
            Log.d(TAG, "=== DIRECTORY STRUCTURE ===");
            logDirectoryRecursive(dir, 0);
        } else {
            Log.e(TAG, "Directory not found: " + path);
        }
    }

    private void logDirectoryRecursive(File dir, int depth) {
        String indent = "";
        for (int i = 0; i < depth; i++) indent += "  ";

        File[] files = dir.listFiles();
        if (files != null) {
            for (File file : files) {
                if (file.isDirectory()) {
                    Log.d(TAG, indent + "[DIR] " + file.getName() + "/");
                    logDirectoryRecursive(file, depth + 1);
                } else {
                    Log.d(TAG, indent + "[FILE] " + file.getName() + " (" + file.length() + " bytes)");
                }
            }
        }
    }

    private void deleteDir(File dir) {
        if (dir.isDirectory()) {
            File[] children = dir.listFiles();
            if (children != null) {
                for (File child : children) {
                    deleteDir(child);
                }
            }
        }
        dir.delete();
    }
}