#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cmath>
#include <iomanip>

#include "Vector.h"
#include "Matrix4x4.h"

template <typename T>
Vec4<T> sphericalToCartesion(const T&, const T&);
template <typename T>
T sphericalTheta(const Vec4<T>&);
template <typename T>
T sphericalPhi(const Vec4<T>&);

template <typename T>
std::ostream& operator<<(std::ostream &os, Vec4<T> &vObj);
template <typename T>
std::ostream& operator<<(std::ostream &os, Mat44<T> &matObj);

typedef float Point[3];

void projectedPoints(const uint32_t &w, const uint32_t &h, const Point (&c)[8]);

int main(){
    Point corners[8] = {
        { 1, -1, -5},
        { 1, -1, -3},
        { 1,  1, -5},
        { 1,  1, -3},
        {-1, -1, -5},
        {-1, -1, -3},
        {-1,  1, -5},
        {-1,  1, -3}
    };

    uint32_t image_width = 1024; 
    uint32_t image_height = 512;

    Mat44<float> m(0.718762f, 0.615033f, -0.324214f, 0.0f, -0.393732f, 0.744416f, 0.539277f, 0, 0.573024f, -0.259959f, 0.777216f, 0.0f, 0.526967f, 1.254234f, -2.53215f, 1.0f);

    Vec4<float> pLocal(-0.5f, 0.5f, -0.5f), pWorld;

    pWorld = pLocal * m;

    std::cout << pWorld << "\n";

    return 0;
}

template <typename T>
Vec4<T> sphericalToCartesion(const T& theta, const T& phi){
    return Vec4<T>(cos(phi) * sin(theta), cos(theta) * sin(phi), cos(theta));
}

// template <typename T>
// T sphericalTheta(const Vec4<T>& v){
//     return acos(clamp<T>(v[2], T(-1), T(1)));
// }

template <typename T>
T sphericalPhi(const Vec4<T>& v){
    T p = atan2(v[1], v[0]);
    return (p < 0)? p + 2 * M_PI: p;
}

template <typename T>
std::ostream& operator<<(std::ostream &os, Vec4<T> &vObj){
    os << "(x: " << vObj.x << ", y: " << vObj.y << ", z: " << vObj.z << ", w: " << vObj.w << ")";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream &os, Mat44<T> &matObj){
    os << '{';
    for(uint8_t row = 0; row < 4; row++){
        os << "[ ";
        for (uint8_t col = 0; col < 4; col++){
            os << matObj.m[row][col];
            if (col < 3) os << ", ";
        }
        os << " ]";
    }
    os << '}';
    return os;
}

void projectedPoints(const uint32_t &w, const uint32_t &h, const Point (&c)[8]){
    float aspect_ratio = w / static_cast<float>(h);

    for (int i = 0; i < 8; i++){
        float x_project = c[i][0] / -c[i][2];
        float y_project = c[i][1] / -c[i][2] * aspect_ratio;

        float x_proj_remap = (1 + x_project) / 2;
        float y_proj_remap = (1 + y_project) / 2;

        float x_proj_pix = x_proj_remap * w;
        float y_proj_pix = y_proj_remap * h;

        std::cout << "X projection point: " << x_proj_pix << "\n";
        std::cout << "Y projection point: " << y_proj_pix << "\n"; 
    }
}