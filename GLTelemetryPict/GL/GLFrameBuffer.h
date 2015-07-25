//
//  GLFrameBuffer.h
//  inseparable
//
//  Created by h on 7/8/14.
//  Copyright (c) 2014 h. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#import  <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>


@interface GLFrameBuffer : NSObject{

    NSSize textureSize;

    GLuint  texture_name;
    GLuint  renderbuffer_name;
    GLuint  framebuffer_name;

}

-(id)initWithSize:(NSSize)size;

-(void)initTexture:(NSSize)size;
-(void)initRenderbuffer:(NSSize)size;
-(void)initFramebuffer:(NSSize)size;


-(void)bind;
-(void)unbind;

-(void)renderBufferTexture;


-(void)bindTexture;
-(void)unbindTexture;


-(void)writeToFile:(NSString*)filePath;

-(GLuint)textureID;


@end
