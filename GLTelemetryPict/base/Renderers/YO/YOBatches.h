//
//  YOBatches.h
//  GLTelemetryPict
//
//  Created by YoshitoONISHI on 8/13/15.
//  Copyright (c) 2015 h. All rights reserved.
//

#ifndef __GLTelemetryPict__YOBatches__
#define __GLTelemetryPict__YOBatches__

namespace YO {

struct RgbColor
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

struct HsvColor
{
    unsigned char h;
    unsigned char s;
    unsigned char v;
};

struct Color {
    float r, g, b, a;
};

struct Vertex {
    float x, y, z;
};

RgbColor HsvToRgb(HsvColor hsv);
HsvColor RgbToHsv(RgbColor rgb);
    
}

#endif /* defined(__GLTelemetryPict__YOBatches__) */
