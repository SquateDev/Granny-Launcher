//
// Created by SquateDevj on 21.05.2026.
//

#ifndef AKIRONLAUNCHER_LOCALPLAYER_H
#define AKIRONLAUNCHER_LOCALPLAYER_H
#include <include/vector.h>

class LocalPlayer {
public:
    static void init();
    static void setPos(float x, float y, float z);
    static char* getPosText();
    static void incsressGranny();
    static void decressGranny();
    static void incressMom();
    static void deincressMom();
    static void godmode(bool godmode, bool granny_mode, bool momspider_mode, bool spider_mode, bool falldamage_mode);
    static bool getGame();
};

#endif //AKIRONLAUNCHER_LOCALPLAYER_H
