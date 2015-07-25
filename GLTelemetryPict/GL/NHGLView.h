//
//  NHGLView.h
//  GL
//
//  Created by h on 6/24/15.
//  Copyright (c) 2015 h. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import  <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>

#import "NHGLWrapper.h"


@interface NHGLView : NSOpenGLView{


    

}

-(void)setVBLSync:(bool)b;

@end





