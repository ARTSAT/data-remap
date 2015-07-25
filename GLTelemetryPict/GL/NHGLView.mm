//
//  NHGLView.m
//  GL
//
//  Created by h on 6/24/15.
//  Copyright (c) 2015 h. All rights reserved.
//

#import "NHGLView.h"

#define BITS_PER_PIXEL          32
#define DEPTH_SIZE              32


@implementation NHGLView

-(id)initWithFrame:(NSRect) frameRect{

    NSLog(@"%s @ w = %.0f ,  h = %.0f",__FUNCTION__,frameRect.size.width,frameRect.size.height);

    NSOpenGLPixelFormatAttribute attr[] =
    {
        NSOpenGLPFADoubleBuffer,
        NSOpenGLPFAAccelerated,
        NSOpenGLPFAColorSize, BITS_PER_PIXEL,
        NSOpenGLPFADepthSize, DEPTH_SIZE,
        0
    };


    self = [super initWithFrame:frameRect
                    pixelFormat:[[NSOpenGLPixelFormat alloc] initWithAttributes:attr]];

    [[self openGLContext] makeCurrentContext];
    [self setPostsFrameChangedNotifications: YES];
    [self initGL];
    [self setVBLSync:true];

    return self;
}



-(id)initWithFrame:(NSRect) frameRect
       withContext:(NSOpenGLContext*)context{

    self = [self initWithFrame:frameRect];

    [self setOpenGLContext:context];

    return  self;
}

- (void)initGL{

    glClearColor(0,0,0,0);
    glClearDepth(.0f);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);
    glColorMaterial( GL_FRONT_AND_BACK, GL_DIFFUSE );
    glEnable(GL_COLOR_MATERIAL);

    glDisable( GL_BLEND );
    glDisable(GL_DEPTH_TEST);
}

-(void)setVBLSync:(bool)b{

    const GLint swapInterval = b;
    [[self openGLContext] setValues:&swapInterval forParameter:NSOpenGLCPSwapInterval];
    
}


@end


