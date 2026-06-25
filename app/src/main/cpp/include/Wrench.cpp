#include "Wrench.h"
#include <dlfcn.h>
#include "include/Logger.h"

const char* LIB = "libil2cpp.so";

void* Wrench::getBaseAddress(uintptr_t offset){
    void* handle = dlopen(LIB, RTLD_LAZY);
    if(!handle){
        LOGI("Not Library");
        return nullptr;
    }
    void* sym = dlsym(handle, "JNI_OnLoad");
    if(!sym){
        sym = dlsym(handle, "init");
    }
    if(!sym){
        LOGI("Символ не найден");
        dlclose(handle);
        return nullptr;
    }
    Dl_info info;
    uintptr_t base_addres = 0;
    if(dladdr(sym, &info)){
        base_addres = reinterpret_cast<uintptr_t >(info.dli_fbase);
    }
    dlclose(handle);
    if(base_addres == 0) return nullptr;

    uintptr_t target_adress = base_addres + offset;
    return reinterpret_cast<void*>(target_adress);
}

uintptr_t Wrench::getMap() {
    void* handle = dlopen(LIB, RTLD_LAZY);
    if(!handle){
        LOGI("Not Library");
        return 0;
    }
    void* sym = dlsym(handle, "JNI_OnLoad");
    if(!sym){
        sym = dlsym(handle, "init");
    }
    if(!sym){
        LOGI("Символ не найден");
        dlclose(handle);
        return 0;
    }
    Dl_info info;
    uintptr_t base_addres = 0;
    if(dladdr(sym, &info)){
        base_addres = reinterpret_cast<uintptr_t >(info.dli_fbase);
    }
    dlclose(handle);
    if(base_addres == 0) return 0;
    return base_addres;
}

void *Wrench::getFunc(const char *text) {
    void* lib_handle = dlopen(LIB, RTLD_LAZY);
    void* func =  dlsym(lib_handle, text);
    return func;
}

char* Wrench:: Utf16ToAscii(const uint16_t* utf16, int maxLen) {
    char* result;
    if(!utf16) return result;

    int i = 0;
    while(utf16[i] != 0 && (maxLen == -1 || i < maxLen)) {
        if(utf16[i] < 0x80) {
            result += (char)utf16[i];
        } else {
            result += '?';
        }
        i++;
    }
    return result;
}
