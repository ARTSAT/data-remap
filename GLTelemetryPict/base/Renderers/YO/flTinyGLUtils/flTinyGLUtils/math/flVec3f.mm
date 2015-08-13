//
//  flVec3f.cpp
//  workYO
//
//  Created by YoshitoONISHI on 6/7/15.
//  Copyright (c) 2015 r. All rights reserved.
//

#include "flVec3f.h"
#include "flVec2f.h"
#include "flVec4f.h"

FL_NAMESPACE_BEGIN

Vec3f::Vec3f(const Vec2f& vec) : x(vec.x), y(vec.y), z(0.f) {}
Vec3f::Vec3f(const Vec4f& vec) : x(vec.x), y(vec.y), z(vec.z) {}

FL_NAMESPACE_END