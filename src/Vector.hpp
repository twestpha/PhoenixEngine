#pragma once

struct Vector2 {
    float x, y;

    VectorX(float x, float y, float z, float w){
        this->x = x;
        this->y = y;
    }
};

struct Vector3 {
    float x, y, z;

    VectorX(float x, float y, float z, float w){
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

struct Vector4 {
    float x, y, z, w;

    VectorX(float x, float y, float z, float w){
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }
};
