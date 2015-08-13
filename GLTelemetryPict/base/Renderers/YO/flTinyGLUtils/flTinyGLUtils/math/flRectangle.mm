//
//  flRectangle.cpp
//  workYO
//
//  Created by YoshitoONISHI on 6/7/15.
//  Copyright (c) 2015 r. All rights reserved.
//

#include "flRectangle.h"

FL_NAMESPACE_BEGIN

Rectangle::Rectangle() :
x(0.f),
y(0.f),
w(0.f),
h(0.f)
{
    
}

Rectangle::Rectangle(float x, float y, float w, float h) :
x(x),
y(y),
w(w),
h(h)
{
    
}

Rectangle::Rectangle(float w, float h) :
x(0.f),
y(0.f),
w(w),
h(h)
{
    
}

FL_NAMESPACE_END