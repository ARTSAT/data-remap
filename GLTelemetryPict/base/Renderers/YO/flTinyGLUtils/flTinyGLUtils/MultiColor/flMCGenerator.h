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
                double arg0, double arg1, double arg2, double arg3,
                double arg4, double arg5, double arg6, double arg7,
                double arg8, double arg9, double arg10);
Vector wrinkled(Vector point, double lacunarity, double H, double octaves);
double multifractal(Vector pos,
                    double H,
                    double lacunarity,
                    double octaves,
                    double zero_offset);

MULTI_COLOR_NAMESPACE_END

#endif