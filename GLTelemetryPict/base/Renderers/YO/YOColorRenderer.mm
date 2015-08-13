//
//  YOColorRenderer.m
//  GLTelemetryPict
//
//  Created by YoshitoONISHI on 8/13/15.
//  Copyright (c) 2015 h. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "YOColorRenderer.h"
#import "NHRenderer.h"

@implementation YOColorRenderer

-(id)init
{
    if ((self = [super init])) {
    }
    return self;
}

-(void)renderFromUnixTime:(int)sec
                 duration:(int)duration
{
    vector<telemetry> telems = reader->telemetriesInRange(sec, duration);
    
    glLineWidth(1);
    glPointSize(1);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    
}

@end