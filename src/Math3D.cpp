#include "Math3D.hpp"

namespace TMath {

float TInverseSqrt(float x){
    // Inverse Sqrt from Quake
    float halfx = 0.5f * x;
    int i = *(int*)&x;              // store floating-point bits in integer
    i = 0x5f3759df - (i >> 1);      // initial guess for Newton's method
    x = *(float*)&i;                // convert new bits into float
    x = x * (1.5f - halfx * x * x); // Two rounds of Newton's method
    x = x * (1.5f - halfx * x * x);

    return x;
}

float TFastSqrt(float x){ // Probably stupidly more expensive...?
    return 1.0f/TInverseSqrt(x);
}

} // namespace TMath
