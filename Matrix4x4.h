#pragma once

#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cmath>

#include "Vector.h"

template <typename T>
class Mat44 {
public:
    T m[4][4];

    Mat44(){
        for (uint8_t row = 0; row < 4; row++){
            for (uint8_t col = 0; col < 4; col++){
                m[row][col] = T(0);
            }
        }
    }

    Mat44(const T arr[4][4]){
        for (uint8_t row = 0; row < 4; row++){
            for (uint8_t col = 0; col < 4; col++){
                m[row][col] = arr[row][col];
            }
        }
    }

    Mat44 (T a, T b, T c, T d, T e, T f, T g, T h,
        T i, T j, T k, T l, T _m, T n, T o, T p){
        m[0][0] = a;
        m[0][1] = b;
        m[0][2] = c;
        m[0][3] = d;
        m[1][0] = e;
        m[1][1] = f;
        m[1][2] = g;
        m[1][3] = h;
        m[2][0] = i;
        m[2][1] = j;
        m[2][2] = k;
        m[2][3] = l;
        m[3][0] = _m;
        m[3][1] = n;
        m[3][2] = o;
        m[3][3] = p;
    }

    static Mat44<T> Identity() {
        Mat44<T> mat;
        for (int i = 0; i < 4; ++i) mat.m[i][i] = T(1);
        return mat;
    }

    Mat44<T> transpose() const{
        Mat44<T> result;
        for (uint8_t row = 0; row < 4; row++){
            for (uint8_t col = 0; col < 4; col++){
                result.m[row][col] = m[col][row];
            }
        }
        return result;
    }

    T determint() const {
        T result;
        result = m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2]) - m[0][1] * (m[1][0] * m[2][2] - m[2][0] * m[1][2]) + m[0][2] * (m[1][0] * m[2][1] - m[2][0] * m[1][1]);
        return result;
    }

    Mat44<T> adjoint() const {
        Mat44 cofactor;

        cofactor[0][0] = m[1][1] * m[2][2] - m[2][1] * m[1][2]; 
        cofactor[0][1] = m[1][0] * m[2][2] - m[2][0] * m[1][2];
        cofactor[0][2] = m[1][0] * m[2][1] - m[2][0] * m[1][1];

        cofactor[1][0] = m[0][1] * m[2][2] - m[2][1] * m[0][2];
        cofactor[1][1] = m[0][0] * m[2][2] - m[2][0] * m[0][2];
        cofactor[1][2] = m[0][0] * m[2][1] - m[2][0] * m[0][1];

        cofactor[2][0] = m[0][1] * m[1][2] - m[1][1] * m[0][2];
        cofactor[2][1] = m[0][0] * m[1][2] - m[1][0] * m[0][2];
        cofactor[2][2] = m[0][0] * m[1][1] - m[1][0] * m[0][1];

        return cofactor.transpose();
    }

    Mat44<T> inverse() const {
        T det = determint();
        if(det == 0){
            return m;
        }
        T invDet = T(1) / det;
        Mat44<T> adj = adjoint();

        return adj * invDet;
    }

    T* operator[](uint8_t row){return m[row];}
    const T* operator[](uint8_t row) const {return m[row];}

    Mat44<T> operator*(T t){
        Mat44 result;
        for (uint8_t i = 0; i < 4; i++){
            for (uint8_t j = 0; j < 4; j++){
                result[i][j] = m[i][j] * t;
            }
        }
        return result;
    }
};