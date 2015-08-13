//
//  flEasing.cpp
//  flTinyGLUtils
//
//  Created by YoshitoONISHI on 6/14/15.
//  Copyright (c) 2015 YoshitoONISHI. All rights reserved.
//

#include "flEasing.h"

using namespace::std;

FL_NAMESPACE_BEGIN

std::function<void(float&, float)> fadeInNormal = std::bind(fadeIn, std::placeholders::_1, std::placeholders::_2, 1.f, 1.f);
std::function<void(float&, float)> fadeOutNormal  = std::bind(fadeOut, std::placeholders::_1, std::placeholders::_2, 0.f, 1.f);


FL_NAMESPACE_END