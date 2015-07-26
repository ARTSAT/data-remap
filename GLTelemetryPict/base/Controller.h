//
//  Controller.h
//  GL
//
//  Created by h on 6/26/15.
//  Copyright (c) 2015 h. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "NHGLView.h"
#import "GLFrameBuffer.h"
#import "NHGLWrapper.h"
#import "config.h"
#import "Renderer.h"
#import "AzimuthRenderer.h"



@interface Controller : NSObject{


    NHGLView *glView;
    NSWindow *fsWindow;

    GLFrameBuffer *fbo;


    Renderer *targetRenderer;
    AzimuthRenderer *azimuthRanderer;
    
    IBOutlet NSTextField *indexLabel;
}


-(IBAction)toggleFit:(id)sender;
-(IBAction)exportPNGs:(id)sender;
-(IBAction)changeRenderingTargetTime:(id)sender;



@end
