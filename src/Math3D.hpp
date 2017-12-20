#ifndef MATH3D_H
#define MATH3D_H

namespace TMath {

// Custom Math Definitions
float TInverseSqrt(float x);
float TFastSqrt(float x);

} // namespace TMath

// Vector Definitions

struct Vector2 {
    float x, y;

    Vector2(){
        x = y = 0.0f;
    }

    Vector2(float x, float y){
        this->x = x;
        this->y = y;
    }

    float Dot(Vector2 other){
        return (x * other.x) + (y * other.y);
    }

    float MagnitudeSquared(){
        return this->Dot(*this);
    }

    float Magnitude(){
        return TMath::TFastSqrt(MagnitudeSquared());
    }
};

struct Vector3 {
    float x, y, z;

    Vector3(){
        x = y = z = 0.0f;
    }

    Vector3(float x, float y, float z){
        this->x = x;
        this->y = y;
        this->z = z;
    }

    float Dot(Vector3 other){
        return (x * other.x) + (y * other.y) + (z * other.z);
    }

    float MagnitudeSquared(){
        return this->Dot(*this);
    }

    float Magnitude(){
        return TMath::TFastSqrt(MagnitudeSquared());
    }
};

struct Vector4 {
    float x, y, z, w;

    Vector4(){
        x = y = z = w = 0.0f;
    }

    Vector4(float x, float y, float z, float w){
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    float Dot(Vector4 other){
        return (x * other.x) + (y * other.y) + (z * other.z) + (w * other.w);
    }

    float MagnitudeSquared(){
        return this->Dot(*this);
    }

    float Magnitude(){
        return TMath::TFastSqrt(MagnitudeSquared());
    }
};

// Vector Math Definitions

#endif // MATH3D_H
