//
//  AzimuthRenderer.h
//  GLTelemetryPict
//
//  Created by Koichiro Mori on 2015/07/26.
//  Copyright (c) 2015年 h. All rights reserved.
//

#import "config.h"
#import "charTex.h"

#import "Renderer.h"
#import "telemetryReader.h"
#import "telemetryReaderAzimuth.h"

typedef struct {
    float y;
    float x;
}PointAzimuth;

@interface AzimuthRenderer : Renderer {

@private

    int offsetY;
    telemetryReaderAzimuth *telemetry_az;
}

@end