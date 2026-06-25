//
// Created by SquateDevj on 21.05.2026.
//

#ifndef AKIRONLAUNCHER_WRENCH_H
#define AKIRONLAUNCHER_WRENCH_H

#include <stdint.h>

class Wrench {
public:
    static void* getBaseAddress(unsigned long offset);
    static uintptr_t getMap();
    static void* getFunc(const char* text);
    static char*  Utf16ToAscii(const uint16_t* utf16, int maxLen = -1);
};


#endif //AKIRONLAUNCHER_WRENCH_H
