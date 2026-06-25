struct Vector3 {
    float x, y, z;
    Vector3(): x(0.0), y(0.0), z(0.0){}
    Vector3(float _x, float _y, float _z): x(_x), y(_y), z(_z){}
};

struct Quaternion {
    float x, y, z, w;
    Quaternion(): x(0.0), y(0.0), z(0.0), w(0.0){}
    Quaternion(float _x, float _y, float _z, float _w): x(_x), y(_y), z(_z), w(_w){}
};

struct Ray {
    Vector3 origin;
    Vector3 direction;
};

struct RaycastHit {
    Vector3 point;
    Vector3 normal;
    float distance;
    void* collider;
    void* transform;
};

struct Color : Vector3 {
    float red, green, blue;
    Color(): red(0.0), green(0.0), blue(0.0){}
    Color(float _red, float _green, float _blue): red(_red), green(_green), blue(_blue){}
};
struct Transform {

};
class Component {

};
class Type {

};
class Material {
public:
};

class GameObject {
public:
};

class Il2CppString {
public:
};

class Texture {
public:
};

class Shader {
public:
};

class Camera {
public:
};