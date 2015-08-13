//
//  flMCGenerator.h
//  flTinyGLUtils
//
//  Created by YoshitoONISHI on 8/12/15.
//  Copyright (c) 2015 YoshitoONISHI. All rights reserved.
//

#ifndef flTinyGLUtils_flMCGenerator_h
#define flTinyGLUtils_flMCGenerator_h

#include "flMCTypes.h"

MULTI_COLOR_NAMESPACE_BEGIN

void multicolor(Vector texture,
                Color *color,
                float arg0, float arg1, float arg2, float arg3,
                float arg4, float arg5, float arg6, float arg7,
                float arg8, float arg9, float arg10);
Vector wrinkled(Vector point, float lacunarity, float H, float octaves);
float multifractal(Vector pos,
                    float H,
                    float lacunarity,
                    float octaves,
                    float zero_offset);

MULTI_COLOR_NAMESPACE_END

#endif