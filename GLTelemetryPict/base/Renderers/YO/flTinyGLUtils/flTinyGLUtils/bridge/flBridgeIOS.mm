//
//  flBridgeIOS.mm
//  DrawXmasTest
//
//  Created by Onishi Yoshito on 11/6/13.
//  Copyright (c) 2013 Onishi Yoshito. All rights reserved.
//

#include "flBridgeIOS.h"
#include "flCommon.h"
#include "flTexture.h"
#include "flException.h"
#include <iostream>

#if defined (TARGET_IOS) || defined (TARGET_OSX)

#if defined (TARGET_IOS)
#import <UIKit/UIKit.h>
#else
#import <Cocoa/Cocoa.h>
#endif

#import <CoreGraphics/CoreGraphics.h>
#import <QuartzCore/QuartzCore.h>

FL_NAMESPACE_BEGIN

void loadTexture(fl::Texture* texture, NSString* file)
{
    @autoreleasepool {
#if defined (TARGET_IOS)
        UIImage *uiImage = [UIImage imageWithContentsOfFile:file];
        if (image == nil) {
            flThrowException("Invalid image path!");
        }
        CGImageRef cgImage = uiImage.CGImage;
#else
        NSImage *image = [[NSImage alloc] initWithContentsOfFile:file];
        if (image == nil) {
            flThrowException("Invalid image path!");
        }
        CGImageSourceRef source = CGImageSourceCreateWithData((__bridge CFDataRef)image.TIFFRepresentation, NULL);
        CGImageRef cgImage =  CGImageSourceCreateImageAtIndex(source, 0, NULL);
#endif
        
        const size_t width = CGImageGetWidth(cgImage);
        const size_t height = CGImageGetHeight(cgImage);
        
        GLubyte *textureData = (GLubyte *)malloc(width * height * 4);
        
        CGContextRef cgContext = CGBitmapContextCreate(textureData,
                                                       width,
                                                       height,
                                                       8,
                                                       width * 4,
                                                       CGImageGetColorSpace(cgImage),
                                                       kCGImageAlphaPremultipliedLast);
        CGContextDrawImage(cgContext, CGRectMake(0.f, 0.f, (float)width, (float)height), cgImage);
        CGContextRelease(cgContext);
#if defined (TARGET_OSX)
        CFRelease(cgImage);
        CFRelease(source);
#endif
        texture->load(GL_RGBA,
                      (GLsizei)width,
                      (GLsizei)height,
                      GL_RGBA,
                      GL_UNSIGNED_BYTE,
                      textureData);
        
        free(textureData);

    }
}

FL_NAMESPACE_END

#endif