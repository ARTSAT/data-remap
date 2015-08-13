//
//  flVec4f.mm
//  workYO
//
//  Created by YoshitoONISHI on 6/7/15.
//  Copyright (c) 2015 r. All rights reserved.
//

#include "flVec4f.h"
#include "flVec2f.h"
#include "flVec3f.h"

FL_NAMESPACE_BEGIN

Vec4f::Vec4f(const Vec2f& vec) :
x(vec.x),
y(vec.y),
z(0.f),
w(0.f)
{
    
}

Vec4f::Vec4f(const Vec3f& vec) :
x(vec.x),
y(vec.y),
z(vec.z),
w(0.f)
{
    
}

FL_NAMESPACE_END