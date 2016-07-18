#ifndef MATH3D_H
#define MATH3D_H

struct Vector2 {
    float x, y;

    Vector2(float x, float y){
        this->x = x;
        this->y = y;
    }
};

struct Vector3 {
    float x, y, z;

    Vector3(float x, float y, float z){
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

struct Vector4 {
    float x, y, z, w;

    Vector4(float x, float y, float z, float w){
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }
};

#endif
