//
//  flBridgeIOS.h
//  flTinyGLUtils
//
//  Created by Onishi Yoshito on 11/6/13.
//  Copyright (c) 2013 Onishi Yoshito. All rights reserved.
//

#ifndef __flTinyGLUtils__flBridgeIOS__
#define __flTinyGLUtils__flBridgeIOS__

// isolate Objective-C++ sources

#if defined (TARGET_IOS) || defined (TARGET_OSX)

#include "flCommon.h"

@class NSString;

FL_NAMESPACE_BEGIN

class Texture;

void loadTexture(fl::Texture* texture, NSString* file);

FL_NAMESPACE_END

#endif

#endif /* defined(__flTinyGLUtils__flBridgeIOS__) */
