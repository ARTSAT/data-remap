//
//  flMCNoise.h
//  flTinyGLUtils
//
//  Created by YoshitoONISHI on 8/12/15.
//  Copyright (c) 2015 YoshitoONISHI. All rights reserved.
//

#ifndef flTinyGLUtils_flMCNoise_h
#define flTinyGLUtils_flMCNoise_h

#include "flMCTypes.h"

MULTI_COLOR_NAMESPACE_BEGIN

void initNoise();
float noise3(Vector vec);
Vector vecNoise3(Vector point);

MULTI_COLOR_NAMESPACE_END

#endif