//
//  flMCGenerator.cpp
//  flTinyGLUtils
//
//  Created by YoshitoONISHI on 8/12/15.
//  Copyright (c) 2015 YoshitoONISHI. All rights reserved.
//

#include "flMCGenerator.h"
#include "flMCNoise.h"

MULTI_COLOR_NAMESPACE_BEGIN

#define VADD(u, v)	((u).x += (v).x, (u).y += (v).y, (u).z += (v).z, (u))
#define SMULT(s, v)	((v).x *= (s), (v).y *= (s), (v).z *= (s), (v))

void multicolor(Vector texture,
                Color *color,
                float arg0, float arg1, float arg2, float arg3,
                float arg4, float arg5, float arg6, float arg7,
                float arg8, float arg9, float arg10 )
{
    Vector axis, purt, cvec;
    Matrix matrix, tmpmat;
    
    copyMatrix(kIdentityMatrix, matrix);
    
    axis = wrinkled(texture, 2.0f, arg4, arg5);
    
    rotateX(arg6 * axis.x, tmpmat);
    multMatrix(matrix, tmpmat, matrix);
    rotateY(arg6 * axis.y, tmpmat);
    multMatrix(matrix, tmpmat, matrix);
    rotateZ(arg6 * axis.z, tmpmat);
    multMatrix(matrix, tmpmat, matrix);
    
    purt = texture;
    SMULT(0.3f, purt);
    purt  = wrinkled(purt, 2.0f, 0.5f, 7.0f);
    SMULT(arg7, purt);
    VADD(texture, purt);
    
    cvec.x = arg10 * multifractal(texture, arg0, arg1, arg2, arg3);
    texture.x += 10.5f;
    cvec.y = arg10 * multifractal(texture, arg0, arg1, arg2, arg3);
    texture.y += 10.5f;
    cvec.z = arg10 * multifractal(texture, arg0, arg1, arg2, arg3);
    
    cvec = vectTransform(cvec, matrix);
    
    color->r += arg8 * cvec.x;
    color->g += arg8 * cvec.y;
    color->b += arg8 * cvec.z;
    
    if (color->r < 0.0f)
        color->r = 0.0f;
    else if (color->r > 1.0f)
        color->r = 1.0f;
    if (color->g < 0.0f)
        color->g = 0.0f;
    else if (color->g > 1.0f)
        color->g = 1.0f;
    if (color->b < 0.0f)
        color->b = 0.0f;
    else if (color->b > 1.0f)
        color->b = 1.0f;
}

Vector wrinkled(Vector point, float lacunarity, float H, float octaves)
{
    Vector sPoint, result, temp;
    float f, s;
    
    result.x = result.y = result.z = 0.0f;
    f = s = 1.0f;
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

float multifractal(Vector pos,
                    float H,
                    float lacunarity,
                    float octaves,
                    float zero_offset)
{
    float y = 1.0f;
    float f = 1.0f;
    
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