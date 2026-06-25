#include <dobby.h>
#include "LocalPlayer.h"
#include "include/Logger.h"
#include <include/Wrench.h>
#include <stdio.h>
#include <string.h>


bool clone_grannys = false;
bool mom_clones = false;


bool godmodes = false;
bool godmode_granny_mode = false;
bool godmode_momspider = false;
float red = 1.0f;
float green = 0.0f;
float blue = 0.0f;
float speed = 0.007f;
bool eyecolor = true;


GameObject* clone_list_granny[50];
GameObject* clone_list_momspider[50];
int clone_cout_g = 0;
int clone_cout_m = 0;
Transform* uk_tran = nullptr;
GameObject* granny = nullptr;
Camera* cameras = nullptr;
GameObject* mom_head = nullptr;
void* granny_enemy = nullptr;

void (*setpos_original)(Transform* uk, Vector3);
Vector3 (*getPos)(Transform*);
void* (*clone_object)(GameObject* object, Vector3 position, Quaternion quaternion);
void (*destory_object)(GameObject*);
void (*setActive)(GameObject*, bool);
Component* (*GetComponent)(void* thiz, Il2CppString* types);
Material* (*getMaterial)(void* thiz);
void (*setColor)(Material*, Vector3);
Il2CppString* (*il2cpp_new_string)(const char* text);
uint16_t* (*getStringToChar)(Il2CppString*);
Il2CppString* (*getTagObject)(void*);
Shader* (*getShader)(Material* shader);
void (*setShader)(Material* material, Shader* shader);
Texture* (*getTexture)(Material*);
void (*setTexture)(Material*, Texture*);
void (*setSizeTexture_Height)(Texture*, int size);
Camera* (*getMainCamera)();
void (*set_fieldOfView)(Camera* , float fov);
void (*set_nearClipPlane)(Camera*, float plan);
void (*set_farClipPlane)(Camera*, float plan);
float (*get_nearClipPlane)(Camera*);
float (*get_farClipPlane)(Camera*);
void (*set_cullingMask)(Camera* , int la);
int (*getLayer)(GameObject*);

// DobbyHook Original
void (*granny_update)(void* thiz);
void (*granny_eye)(void*);
void (*camerarender)(Camera*, Camera*);
void (*spider_MomSpiderHead)(void* inst);
void (*spider_MomSpiderEyes)(void*);
void (*script_playerCaught)(void*);

void (*utils_momspider)(void*);

Vector3 vector_granny = Vector3();
Vector3 vector_momspider = Vector3();
GameObject* mom_game = nullptr;

// Doobby Hook

void utils_mom_hook(void* inst){
    return utils_momspider(inst);
}
int f = 1;
void script_playerCaught_hook(void* inst){
    Transform* pos_granny = *(Transform**)((uintptr_t)inst + 0x28);
    Transform* pos_mom = *(Transform**)((uintptr_t)inst + 0x40);
    if (pos_granny){
        vector_granny = getPos(pos_granny);
    }
    if(pos_mom && f == 1){
        vector_momspider = getPos(pos_mom);
        setpos_original(pos_mom, Vector3(11, 21, -7));
        LOGI("X : %f Y : %f Z : %f", vector_momspider.x, vector_momspider.y, vector_momspider.z);
    }
    return script_playerCaught(inst);
}

void spider_MomSpiderHead_hook(void* inst){
    mom_head = (GameObject*)inst;

    if(godmodes && godmode_momspider){
        *(bool*)((uintptr_t)inst + 0x40) = false; // seePlayer

        *(bool*)((uintptr_t)inst + 0x41) = false; // Hunting

        *(bool*)((uintptr_t)inst + 0xAC) = false; // playerInHidingSpot

        *(bool*)((uintptr_t)inst + 0xAE) = false; // LookingAtPlayer

        *(bool*)((uintptr_t)inst + 0xC0) = false; // playerCaught

        *(bool*)((uintptr_t)inst + 0x120) = false; // redEyeOn
    }

    return spider_MomSpiderHead(inst);
}


void spider_MomSpiderEyes_hook(void* inst){
    mom_game =  *(GameObject**)((uintptr_t)inst + 0x40);
    if(mom_clones){
        if(clone_cout_m < 50 && mom_head && mom_game){
            if(vector_momspider.x == 0 || vector_momspider.y == 0 || vector_momspider.z == 0) {
                clone_list_momspider[clone_cout_m] = (GameObject *) clone_object(mom_game,
                                                                                 Vector3(11, 21, -7),
                                                                                 Quaternion(0, 0, 0,
                                                                                            0));
            } else {
                clone_list_momspider[clone_cout_m] = (GameObject *) clone_object(mom_game,
                                                                                 vector_momspider,
                                                                                 Quaternion(0, 0, 0,
                                                                                            0));
            }clone_cout_m++;
            mom_clones = false;
            mom_head = nullptr;
        } else {
            mom_clones = false;
            mom_head = nullptr;
        }
    }
    if(godmodes && godmode_momspider){
        *(bool*)((uintptr_t)inst + 0x4C) = false; // seePlayer
        *(bool*)((uintptr_t)inst + 0x58) = false; // seePlayer R
        *(bool*)((uintptr_t)inst + 0x68) = false; // seePlayer L
        *(float*)((uintptr_t)inst + 0x48) = 0;
    } else {
        *(float*)((uintptr_t)inst + 0x48) = 550.000000;
    }
    return spider_MomSpiderEyes(inst);
}
void camerarender_hook(Camera* camerathiz, Camera* camera){
    cameras = camerathiz; // Для поле зрение и так далее
    return camerarender(camerathiz, camera);
}



void granny_hook(void* thiz){
    granny_enemy = thiz;
    void* eye_color = *(void**)((uintptr_t)thiz + 0x350);

    if(godmodes && godmode_granny_mode){
        *(bool*)((uintptr_t)thiz + 0x198) = false; // SeePlayer
        *(bool*)((uintptr_t)thiz + 0x199) = false; // SeePlayer Timer
        *(bool*)((uintptr_t)thiz + 0x1D1) = false; // attackingPlayer
        *(bool*)((uintptr_t)thiz + 0x1D2) = false; // huntPlayer
        *(bool*)((uintptr_t)thiz + 0x1D3) = false; // grannyIsFollow
        *(bool*)((uintptr_t)thiz + 0x1E2) = false; // startAttack

        *(bool*)((uintptr_t)thiz + 0x1E5) = false; // playerHidingUnderBed
        *(bool*)((uintptr_t)thiz + 0x1E8) = false; // playerHidingInCar

        *(bool*)((uintptr_t)thiz + 0x1E6) = false; // playerHidingInCoffin
        *(bool*)((uintptr_t)thiz + 0x1E7) = false; // playerHidingInCoffinBackyard

        *(bool*)((uintptr_t)thiz + 0x1EA) = false; // grannyLookUnderBed

        *(bool*)((uintptr_t)thiz + 0x33D) = false; // playerHaveTeddy

        *(bool*)((uintptr_t)thiz + 0x33B) = false; // playerNearGranny

        *(bool*)((uintptr_t)thiz + 0x33C) = false; // GrannyGonnaSmack

        *(bool*)((uintptr_t)thiz + 0x3C8) = false; // playerStandBed

        *(bool*)((uintptr_t)thiz + 0x33F) = false; // playerStartCar

        *(bool*)((uintptr_t)thiz + 0x340) = false; // grannyEyeColorTimerOn

        *(bool*)((uintptr_t)thiz + 0x338) = false; // turnFacePlayer

        *(bool*)((uintptr_t)thiz + 0x33E) = false; // spiderIsDead

        *(float*)((uintptr_t)thiz + 0x1B8) = 0.0; // timerSee
    }

    if(eyecolor){
        if(il2cpp_new_string) {
            const char* txt = "Renderer";
            Il2CppString* text = il2cpp_new_string(txt);
            Component *component = GetComponent(eye_color, text);
            if(component){
                Material* material = getMaterial(component);
                if(material){
                    if(red > 0.0f && green < 1.0f && blue == 0.0f){
                        red -= speed;
                        green += speed;
                        if(red < 0.0f) red = 0.0f;
                        if(green > 1.0f) green = 1.0f;
                    }
                    else if(red == 0.0f && green > 0.0f && blue < 1.0f){
                        green -= speed;
                        blue += speed;
                        if(green < 0.0f) green = 0.0f;
                        if(blue > 1.0f) blue = 1.0f;
                    }

                    else if(red < 1.0f && green == 0.0f && blue > 0.0f){
                        blue -= speed;
                        red += speed;
                        if(blue < 0.0f) blue = 0.0f;
                        if(red > 1.0f) red = 1.0f;
                    }
                    setColor(material, Vector3(red, green, blue));
                } else {
                    LOGI("Material Null");
                }
            } else {
                LOGI("commponent null");
            }
        } else {
            LOGI("il2cpp null");
        }
    }

    return granny_update(thiz);
}

void granny_eye_hook(void* inst){
    granny = *(GameObject**)((uintptr_t)inst + 0x40);
    if(clone_grannys == true){
        if(clone_cout_g < 50 && granny_enemy){
            if(vector_granny.x == 0 || vector_granny.y == 0 || vector_granny.z == 0) {
                clone_list_granny[clone_cout_g] = (GameObject *) clone_object(granny,
                                                                              Vector3(11, 21, -7),
                                                                              Quaternion(0, 0, 0,
                                                                                         0));
            } else {
                clone_list_granny[clone_cout_g] = (GameObject *) clone_object(granny,
                                                                              vector_granny,
                                                                              Quaternion(0, 0, 0,
                                                                                         0));
            }
            clone_cout_g++;
            clone_grannys = false;
            granny_enemy = nullptr;
        } else {
            clone_grannys = false;
            granny_enemy = nullptr;
        }
    }
    return granny_eye(inst);
}

void LocalPlayer::init() {
    void* addr = nullptr;
    addr =  Wrench::getBaseAddress(0x142110C);
    if(addr){
        DobbyHook(addr, (void*)granny_hook, (void**)&granny_update);
    }
    addr = Wrench::getBaseAddress(0x149E36C);
    if(addr){
        DobbyHook(addr, (void*)granny_eye_hook, (void**)&granny_eye);
    }
    addr = Wrench::getBaseAddress(0x29FCE44);
    if(addr){
        LOGI("CAMERA HOOK");
        DobbyHook(addr, (void*) camerarender_hook, (void**)&camerarender);
    }
    addr = Wrench::getBaseAddress(0x14A1F88);
    if(addr){
        DobbyHook(addr, (void*) spider_MomSpiderEyes_hook, (void**)&spider_MomSpiderEyes);
    }
    addr = Wrench::getBaseAddress(0x14A28C8);
    if(addr){
        DobbyHook(addr, (void*) spider_MomSpiderHead_hook, (void**)&spider_MomSpiderHead);
    }
    addr = Wrench::getBaseAddress(0x15033E8);
    if(addr){
        DobbyHook(addr, (void*) script_playerCaught_hook, (void**)&script_playerCaught);
    }
    addr = Wrench::getBaseAddress(0x14AA248);
    if(addr){
        DobbyHook(addr, (void*) utils_mom_hook, (void**)&utils_momspider);
    }
    setpos_original = (void(*)(Transform*, Vector3))Wrench::getBaseAddress(0x2A37BE8);
    getPos = (Vector3(*)(Transform*)) Wrench::getBaseAddress(0x2A37B14);
    clone_object = (void* (*)(GameObject*, Vector3, Quaternion)) Wrench::getBaseAddress(0x2A31D58);
    destory_object = (void (*)(GameObject*)) Wrench::getBaseAddress(0x2A32138);
    setActive = (void (*)(GameObject*, bool)) Wrench::getBaseAddress(0x2A2CC18);
    GetComponent = (Component* (*)(void*, Il2CppString* types)) Wrench::getBaseAddress(0x2A2C0FC);
    getMaterial = (Material* (*)(void* thiz)) Wrench::getBaseAddress(0x2A08B70);
    setColor = (void (*)(Material*, Vector3)) Wrench::getBaseAddress(0x2A09FD0);
    getTagObject = (Il2CppString* (*)(void*)) Wrench::getBaseAddress(0x2A2981C);
    // Texture
    getShader = (Shader* (*)(Material*)) Wrench::getBaseAddress(0x2A09C9C);
    setShader = (void (*)(Material* , Shader*)) Wrench::getBaseAddress(0x2A09D90);
    getTexture = (Texture* (*)(Material*))  Wrench::getBaseAddress(0x2A09D90);
    setTexture = (void (*)(Material* , Texture*)) Wrench::getBaseAddress(0x2A0A0F0);
    setSizeTexture_Height = (void (*)(Texture*, int)) Wrench::getBaseAddress(0x2A0FEC0);

    // Camera
    getMainCamera = (Camera* (*)()) Wrench::getBaseAddress(0x29FC934);
    set_fieldOfView = (void (*)(Camera*, float)) Wrench::getBaseAddress(0x29FAD20);
    set_nearClipPlane = (void (*)(Camera*, float)) Wrench::getBaseAddress(0x29FAA10);
    set_farClipPlane = (void (*)(Camera*, float)) Wrench::getBaseAddress(0x29FAB98);
    get_nearClipPlane = (float (*)(Camera*)) Wrench::getBaseAddress(0x29FA95C);
    get_farClipPlane = (float (*)(Camera*)) Wrench::getBaseAddress(0x29FAAE4);
    set_cullingMask = (void (*)(Camera*, int)) Wrench::getBaseAddress(0x29FB4A8);
    getLayer = (int (*)(GameObject*)) Wrench::getBaseAddress(0x2A2CAB0);

    // Text
    getStringToChar = (uint16_t* (*)(Il2CppString*)) Wrench::getFunc("il2cpp_string_chars");
    il2cpp_new_string = (Il2CppString*(*)(const char*)) Wrench::getFunc("il2cpp_string_new");
}

char *LocalPlayer::getPosText() {
    if(uk_tran== nullptr || uk_tran == NULL) return "X: 0.0 | Y: 0.0 | Z: 0.0";
    Vector3 pos = getPos(uk_tran);
    uk_tran = nullptr;
    static char buffer[64];
    snprintf(buffer, sizeof(buffer), "X: %.1f | Y: %.1f | Z: %.1f", pos.x, pos.y, pos.z);
    return buffer;
}

void LocalPlayer::setPos(float x, float y, float z) {
    if(uk_tran != nullptr || uk_tran != NULL || setpos_original != nullptr || setpos_original != NULL){
        setpos_original(uk_tran, Vector3(x, y, z));
    }
}

void LocalPlayer::incsressGranny() {
    clone_grannys = true;
}

void LocalPlayer::decressGranny() {
    if(clone_cout_g > 0){
        clone_cout_g--;
        if(clone_list_granny[clone_cout_g] == nullptr){
            return;
        }
        destory_object(clone_list_granny[clone_cout_g]);
        clone_list_granny[clone_cout_g] = nullptr;
    }
}

void LocalPlayer::godmode(bool godmode, bool granny_mode, bool momspider_mode, bool spider_mode, bool falldamage_mode) {
    godmodes = godmode;
    godmode_granny_mode = granny_mode;
    godmode_momspider = momspider_mode;
}

bool LocalPlayer::getGame() {
    if(granny_enemy){
        return true;
    } else {
        return false;
    }
}

void LocalPlayer::incressMom() {
    mom_clones = true;
}

void LocalPlayer::deincressMom() {
    if(clone_cout_m > 0){
        clone_cout_m--;
        if(clone_list_momspider[clone_cout_m] == nullptr){
            return;
        }
        destory_object(clone_list_momspider[clone_cout_m]);
        clone_list_momspider[clone_cout_m] = nullptr;
    }
}
