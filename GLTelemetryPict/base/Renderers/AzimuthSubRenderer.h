//
//  AzimuthSubRenderer.h
//  GLTelemetryPict
//
//  Created by Koichiro Mori on 2015/08/14.
//  Copyright (c) 2015年 h. All rights reserved.
//

#ifndef GLTelemetryPict_AZRenderer_h
#define GLTelemetryPict_AZRenderer_h

#import "config.h"
#import "charTex.h"

#import "Renderer.h"
#import "telemetryReader.h"
#import "telemetryReaderAzimuth.h"



@interface AzimuthSubRenderer : Renderer {
    
@private
    BOOL whitening;
    int offsetY;
    telemetryReaderAzimuth *telemetry_az;
}

@end

#endif
