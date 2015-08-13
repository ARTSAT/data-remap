//
//  flMCTypes.cpp
//  flTinyGLUtils
//
//  Created by YoshitoONISHI on 8/13/15.
//  Copyright (c) 2015 YoshitoONISHI. All rights reserved.
//

#include "flMCTypes.h"
#include <math.h>

MULTI_COLOR_NAMESPACE_BEGIN

const Matrix kIdentityMatrix = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
};

void copyMatrix(const Matrix a, Matrix b)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            b[i][j] = a[i][j];
}

void multMatrix(const Matrix a, const Matrix b, Matrix c)
{
    float sum;
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            sum = 0.0;
            for (int k = 0; k < 4; k++)
                sum += a[i][k] * b[k][j];
            c[i][j]= sum;
        }
    }
}

void rotateX(float theta, Matrix m)
{
    float sine = ::sinf(theta);
    float cosine = ::cosf(theta);
    
    copyMatrix(kIdentityMatrix, m);
    m[1][1] = cosine;
    m[2][1] = -sine;
    m[1][2] = sine;
    m[2][2] = cosine;
}

void rotateY(float theta, Matrix m)
{
    float sine = ::sinf(theta);
    float cosine = ::cosf(theta);
    
    copyMatrix(kIdentityMatrix, m);
    m[0][0] = cosine;
    m[2][0] = sine;
    m[0][2] = -sine;
    m[2][2] = cosine;
}

void rotateZ(float theta, Matrix m)
{
    float sine = ::sinf(theta);
    float cosine = ::cosf(theta);
    
    copyMatrix(kIdentityMatrix, m);
    m[0][0] = cosine;
    m[1][0] = -sine;
    m[0][1] = sine;
    m[1][1] = cosine;
}

Vector vectTransform(const Vector v, const Matrix m)
{
    Vector vPrime;
    
    vPrime.x = v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0] + m[3][0];
    vPrime.y = v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1] + m[3][1];
    vPrime.z = v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2] + m[3][2];
    
    return vPrime;
}

MULTI_COLOR_NAMESPACE_END