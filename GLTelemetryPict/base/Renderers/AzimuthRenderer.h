//
//  AzimuthRenderer.h
//  GLTelemetryPict
//
//  Created by Koichiro Mori on 2015/07/26.
//  Copyright (c) 2015年 h. All rights reserved.
//

#import "Renderer.h"
#import "telemetryReader.h"

@interface AzimuthRenderer : Renderer {

@private

    int offsetY;
}

-(void)drawCircle: (float)cx cy:(float)cy r:(float)r num_segments:(int)num_segments;

@end