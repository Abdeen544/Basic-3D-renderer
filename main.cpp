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

bool computePixelCoordinate(const Vec4<float>& pWorld, const Mat44<float>& cameraToWorld, const float& canvasWidth, const float& canvasHeight, const int& imageWidth, const int& imageHeight, Vec4<int>& pRaster){
    Vec4<float> pCamera;
    Mat44<float> worldToCamera = cameraToWorld.inverse();
    pCamera = pWorld * worldToCamera;

    //Coordinates to points on canvas
    Vec4<float> pScreen;
    pScreen.x = pCamera.x / -pCamera.z;
    pScreen.y = pCamera.y / -pCamera.z;

    //filtering all outside points
    if(std::abs(pScreen.x) > canvasWidth || std::abs(pScreen.y) > canvasHeight){
        return false;
    }

    //Normalize coordinates to [0,1]
    Vec4<float> pNDC;
    pNDC.x = (pScreen.x + canvasWidth * 0.5) / canvasWidth;
    pNDC.y = (pScreen.y + canvasHeight * 0.5) / canvasHeight;

    //Convert to pixel coordinate (rasterization)
    pRaster.x = std::floor(pNDC.x * imageWidth);
    pRaster.y = std::floor((1.0 - pNDC.y) * imageWidth);

    return true;
}

int main(){

    uint32_t image_width = 512; 
    uint32_t image_height = 512;

    Mat44<float> cameraToWorld(0.718762f, 0.615033f, -0.324214f, 0.0f, -0.393732f, 0.744416f, 0.539277f, 0.0f, 0.573024f, -0.259959f, 0.777216f, 0.0f, 0.526967f, 1.254234f, -2.53215f, 1.0f);
    
    Vec4<float> pWorld(-0.315792, 1.4489, -2.48901);

    float canvasWidth = 2.0;
    float canvasHeight = 2.0;

    Vec4<int> pRaster;

    if(computePixelCoordinate(pWorld, cameraToWorld, canvasWidth, canvasHeight, image_width, image_height, pRaster)){
        std::cout << pRaster << "\n";
    } else {
        std::cout << pWorld << " isn't visible\n";
    }

    return 0;
}

template <typename T>
Vec4<T> sphericalToCartesion(const T& theta, const T& phi){
    return Vec4<T>(cos(phi) * sin(theta), cos(theta) * sin(phi), cos(theta));
}

template <typename T>
T sphericalTheta(const Vec4<T>& v){
    return acos(clamp(v.z, T(-1), T(1)));
}

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