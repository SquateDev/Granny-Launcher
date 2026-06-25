#include <jni.h>
#include <string>
#include <dlfcn.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <android/log.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "dobby.h"
#include "KittyMemory/KittyMemory.h"
#include "include/Logger.h"
#include "LocalPlayer/LocalPlayer.h"

static char NEW_PREFIX[1024] = {0};
static bool hooks_installed = false;

typedef int (*open_t)(const char*, int, ...);
typedef DIR* (*opendir_t)(const char*);
typedef int (*stat_t)(const char*, struct stat*);
static open_t open_original = nullptr;
static opendir_t opendir_original = nullptr;
static stat_t stat_original = nullptr;


static bool should_hook(const char* path) {
    if (!path) return false;
    if (strstr(path, "/assets/")) return true;
    if (strstr(path, ".dat")) return true;
    if (strstr(path, ".assets")) return true;
    if (strstr(path, ".split")) return true;
    if (strstr(path, "level")) return true;
    if (strstr(path, "sharedassets")) return true;
    if (strstr(path, "globalgamemanagers")) return true;
    if (strstr(path, "global-metadata")) return true;
    if (strstr(path, "boot.config")) return true;
    if (strstr(path, "Managed")) return true;
    return false;
}

static void replace_prefix(const char* original, char* result, size_t result_size) {
    const char* assets_pos = strstr(original, "/assets/");
    if (assets_pos && NEW_PREFIX[0]) {
        snprintf(result, result_size, "%s%s", NEW_PREFIX, assets_pos);
    } else {
        snprintf(result, result_size, "%s", original);
    }
}

static int open_hook(const char* pathname, int flags, ...) {
    if (pathname && should_hook(pathname) && NEW_PREFIX[0]) {
        char newpath[1024];
        replace_prefix(pathname, newpath, sizeof(newpath));
        mode_t mode = 0;
        if (flags & O_CREAT) {
            va_list args;
            va_start(args, flags);
            mode = va_arg(args, mode_t);
            va_end(args);
        }
        return open_original(newpath, flags, mode);
    }
    return open_original(pathname, flags);
}

static DIR* opendir_hook(const char* pathname) {
    if (pathname && should_hook(pathname) && NEW_PREFIX[0]) {
        char newpath[1024];
        replace_prefix(pathname, newpath, sizeof(newpath));
        return opendir_original(newpath);
    }
    return opendir_original(pathname);
}

static int stat_hook(const char* pathname, struct stat* statbuf) {
    if (pathname && should_hook(pathname) && NEW_PREFIX[0]) {
        char newpath[1024];
        replace_prefix(pathname, newpath, sizeof(newpath));
        return stat_original(newpath, statbuf);
    }
    return stat_original(pathname, statbuf);
}

static void install_hooks() {
    if (hooks_installed) return;
    void* libc = dlopen("libc.so", RTLD_LAZY);
    if (libc) {
        void* ptr = nullptr;
        ptr = dlsym(libc, "open"); if (ptr) { DobbyHook(ptr, (void*)&open_hook, (void**)&open_original); LOGI("HOOKED open"); }
        ptr = dlsym(libc, "opendir"); if (ptr) { DobbyHook(ptr, (void*)&opendir_hook, (void**)&opendir_original); LOGI("HOOKED opendir"); }
        ptr = dlsym(libc, "stat"); if (ptr) { DobbyHook(ptr, (void*)&stat_hook, (void**)&stat_original); LOGI("HOOKED stat"); }
        dlclose(libc);
    }

    hooks_installed = true;
}

extern "C" JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved) {
    return JNI_VERSION_1_6;
}

extern "C" JNIEXPORT void Java_dev_squatedev_akironlauncher_MainActivity_setNativeLoad(JNIEnv * env , jclass clazz, jstring
path ) {
const char *pathStr = env->GetStringUTFChars(path, nullptr);
LOGI("setNativeLoad: %s", pathStr) ;
if ( pathStr &&strlen(pathStr) > 0 ) {
strncpy(NEW_PREFIX, pathStr, sizeof ( NEW_PREFIX ) - 1 ) ;
install_hooks();
}
env->
ReleaseStringUTFChars(path, pathStr
);
}

extern "C" JNIEXPORT void JNICALL Java_dev_squatedev_akironlauncher_MainActivity_loadHook(JNIEnv * env, jclass
clazz) {
    LocalPlayer::init();
}

extern "C"
JNIEXPORT jstring JNICALL
Java_dev_squatedev_akironlauncher_API_LocalPlayer_getPosText(JNIEnv *env, jclass clazz) {
    char* text = LocalPlayer::getPosText();
    jstring java_string = env->NewStringUTF(text);
    return java_string;
}
extern "C"
JNIEXPORT void JNICALL
Java_dev_squatedev_akironlauncher_API_LocalPlayer_setPos(JNIEnv *env, jclass clazz, jfloat x,
                                                         jfloat y, jfloat z) {
LocalPlayer::setPos(x, y, z);
}
extern "C"
JNIEXPORT void JNICALL
Java_dev_squatedev_akironlauncher_API_LocalPlayer_incressGranny(JNIEnv *env, jclass clazz) {
    LocalPlayer::incsressGranny();
}
extern "C"
JNIEXPORT void JNICALL
Java_dev_squatedev_akironlauncher_API_LocalPlayer_deincressGranny(JNIEnv *env, jclass clazz) {
    LocalPlayer::decressGranny();
}
extern "C"
JNIEXPORT void JNICALL
Java_dev_squatedev_akironlauncher_API_LocalPlayer_setGodMode(JNIEnv *env, jclass clazz,
                                                             jboolean godmode, jboolean granny,
                                                             jboolean momspider, jboolean spider,
                                                             jboolean falldamage) {
LocalPlayer::godmode(godmode, granny, momspider, spider, falldamage);
}
extern "C"
JNIEXPORT jboolean JNICALL
Java_dev_squatedev_akironlauncher_API_LocalPlayer_getGame(JNIEnv *env, jclass clazz) {
    return LocalPlayer::getGame();
}
extern "C"
JNIEXPORT void JNICALL
Java_dev_squatedev_akironlauncher_API_LocalPlayer_incressMom(JNIEnv *env, jclass clazz) {
    LocalPlayer::incressMom();
}
extern "C"
JNIEXPORT void JNICALL
Java_dev_squatedev_akironlauncher_API_LocalPlayer_deincressMom(JNIEnv *env, jclass clazz) {
    LocalPlayer::deincressMom();
}