#ifndef DAWN_LOGGER_H
#define DAWN_LOGGER_H
#include <android/log.h>
enum daLogType {
    daDEBUG = 3,
    daERROR = 6,
    daINFO = 4,
    daWARN = 5
};
#define TAG "AkironNative"

#define LOGD(...) ((void)__android_log_print(daDEBUG, TAG, __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(daERROR, TAG, __VA_ARGS__))
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
#define LOGW(...) ((void)__android_log_print(daWARN,  TAG, __VA_ARGS__))

#endif