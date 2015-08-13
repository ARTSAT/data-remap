//
//  flRectangle.h
//  workYO
//
//  Created by YoshitoONISHI on 6/7/15.
//  Copyright (c) 2015 r. All rights reserved.
//

#ifndef __workYO__flRectangle__
#define __workYO__flRectangle__

#include "flCommon.h"

FL_NAMESPACE_BEGIN

struct Size {
    float w, h;
};

struct Rectangle {
    Rectangle();
    explicit Rectangle(float x, float y, float w, float h);
    explicit Rectangle(float w, float h);
    float x, y, w, h;
};

FL_NAMESPACE_END

#endif /* defined(__workYO__flRectangle__) */
