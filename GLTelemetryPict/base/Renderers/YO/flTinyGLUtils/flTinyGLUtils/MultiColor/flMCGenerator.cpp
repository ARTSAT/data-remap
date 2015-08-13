//
//  flMCGenerator.cpp
//  flTinyGLUtils
//
//  Created by YoshitoONISHI on 8/12/15.
//  Copyright (c) 2015 YoshitoONISHI. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include "flMCGenerator.h"
#include "flMCNoise.h"

MULTI_COLOR_NAMESPACE_BEGIN

#define VADD(u, v)	((u).x += (v).x, (u).y += (v).y, (u).z += (v).z, (u))
#define SMULT(s, v)	((v).x *= (s), (v).y *= (s), (v).z *= (s), (v))

void multicolor(Vector texture,
                Color *color,
                double arg0, double arg1, double arg2, double arg3,
                double arg4, double arg5, double arg6, double arg7,
                double arg8, double arg9, double arg10 )
{
    Vector axis, purt, cvec;
    Matrix matrix, tmpmat;
    
    copyMatrix(kIdentityMatrix, matrix);
    
    axis = wrinkled(texture, 2.0, arg4, arg5);
    
    rotateX(arg6 * axis.x, tmpmat);
    multMatrix(matrix, tmpmat, matrix);
    rotateY(arg6 * axis.y, tmpmat);
    multMatrix(matrix, tmpmat, matrix);
    rotateZ(arg6 * axis.z, tmpmat);
    multMatrix(matrix, tmpmat, matrix);
    
    purt = texture;
    SMULT(0.3, purt);
    purt  = wrinkled(purt, 2.0, 0.5, 7.0);
    SMULT(arg7, purt);
    VADD(texture, purt);
    
    cvec.x = arg10 * multifractal(texture, arg0, arg1, arg2, arg3);
    texture.x += 10.5;
    cvec.y = arg10 * multifractal(texture, arg0, arg1, arg2, arg3);
    texture.y += 10.5;
    cvec.z = arg10 * multifractal(texture, arg0, arg1, arg2, arg3);
    
    cvec = vectTransform(cvec, matrix);
    
    color->r += arg8 * cvec.x;
    color->g += arg8 * cvec.y;
    color->b += arg8 * cvec.z;
    
    if (color->r < 0.0)
        color->r = 0.0;
    else if (color->r > 1.0)
        color->r = 1.0;
    if (color->g < 0.0)
        color->g = 0.0;
    else if (color->g > 1.0)
        color->g = 1.0;
    if (color->b < 0.0)
        color->b = 0.0;
    else if (color->b > 1.0)
        color->b = 1.0;
}

Vector wrinkled(Vector point, double lacunarity, double H, double octaves)
{
    Vector sPoint, result, temp;
    double f, s;
    
    result.x = result.y = result.z = 0.0;
    f = s = 1.0;
    for (int i = 0; i < octaves; i++) {
        sPoint.x = f * point.x;
        sPoint.y = f * point.y;
        sPoint.z = f * point.z;
        temp = vecNoise3(sPoint);
        result.x += temp.x * s;
        result.y += temp.y * s;
        result.z += temp.z * s;
        s *= H;
        f *= lacunarity;
    }
    return result;
}

double multifractal(Vector pos,
                    double H,
                    double lacunarity,
                    double octaves,
                    double zero_offset)
{
    double y = 1.0;
    double f = 1.0;
    
    for (int i = 0; i < octaves; i++) {
        y *= zero_offset + f * noise3(pos);
        f *= H;
        pos.x *= lacunarity;
        pos.y *= lacunarity;
        pos.z *= lacunarity;
    }
    
    return y;
}

#undef VADD
#undef SMULT

MULTI_COLOR_NAMESPACE_END