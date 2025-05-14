#ifndef VEC4_H
#define VEC4_H

#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cmath>

#include "Matrix4x4.h"

template <typename T>
class Vec4{
public:
    T x, y, z, w;

    Vec4():x(T(0)), y(T(0)), z(T(0)), w(T(1)){}
    Vec4(const T &xx): x(xx), y(xx), z(xx), w(T(1)){}
    Vec4(T xx, T yy, T zz): x(xx), y(yy), z(zz), w(T(1)){}
    Vec4(T xx, T yy, T zz, T ww): x(xx), y(yy), z(zz), w(ww){}

    T length(){return T(sqrt(x*x + y*y + z*z));}

    static Vec4<T> ZERO(){
        return Vec4<T>(T(0));
    }

    Vec4<T> &normalize(){
        T len = length();
        if(len > 0){
            T invlen = 1 / len;
            x *= invlen;
            y *= invlen;
            z *= invlen;
        }

        return *this;
    }

    T dot(const Vec4<T> &v){
        return T(x * v.x + y * v.y + z * v.z);
    }

    Vec4<T> cross(const Vec4<T> &v){
        return Vec4<T>(y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x);
    }
    
    Vec4<T> operator + (const Vec4<T> &v){
        return Vec4<T>(x + v.x, y + v.y, z + v.z);
    }
    Vec4<T> operator - (const Vec4<T> &v){
        return Vec4<T>(x - v.x, y - v.y, z - v.z);
    }
    Vec4<T> operator * (const Vec4<T> &v){
        return Vec4<T>(x * v.x, y * v.y, z * v.z);
    }
    Vec4<T> operator * (const Mat44<T>& m) const {
        Vec4<T> result;
        result.x = x * m[0][0] + y * m[1][0] + z * m[2][0] + w * m[3][0];
        result.y = x * m[0][1] + y * m[1][1] + z * m[2][1] + w * m[3][1];
        result.z = x * m[0][2] + y * m[1][2] + z * m[2][2] + w * m[3][2];
        result.w = x * m[0][3] + y * m[1][3] + z * m[2][3] + w * m[3][3];
        return result;
    }
};

#endif