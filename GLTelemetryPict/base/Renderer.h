//
//  Renderer.h
//  TelemetryPict
//
//  Created by h on 7/17/15.
//  Copyright (c) 2015 h. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <OpenGL/glu.h>
#import <OpenGL/gl.h>
#import <OpenGL/OpenGL.h>

#import "config.h"
#import "charTex.h"
#include "TLEReader.h"


#import "telemetryReader.h"


@interface Renderer : NSObject{


@public
    telemetryReader *reader;
    charTex *timeCodeText;

    TLEManager *invaderTLE;


    unsigned long deorbitUnixTime;



}

-(void)renderFromUnixTime:(int)sec
                 duration:(int)duration;


@end



@interface TestRenderer : Renderer{


    charTex *smallFont;

}
@end
