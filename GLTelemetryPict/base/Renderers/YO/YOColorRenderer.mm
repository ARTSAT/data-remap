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
#include "flTinyGLUtils.h"
#include "flMCGenerator.h"
#include "flMCNoise.h"

using namespace fl;

@interface YOColorRenderer () {
    vector<shared_ptr<Vbo>> mVbos;
    int mLastSec;
    int mLastDur;
}

@end

@implementation YOColorRenderer

-(id)init
{
    if ((self = [super init])) {
        seedRandom(1);
        MC::initNoise();
        mLastSec = -1;
        mLastDur = -1;
    }
    return self;
}

-(void)renderFromUnixTime:(int)sec
                 duration:(int)duration
{
    auto telems = reader->telemetriesInRange(sec, duration);
    
    ScopedLineWidth lw{1.f};
    ScopedPointSize ps{1.f};
    ScopedBlending bld{BLEND_ALPHA};
    ScopedAlign algn{false};
    ScopedFill fill{true};
    ScopedTranslate t{0.f, ruler_h};
    
    setColor(Color::white);
    enableVertexArray();
    
    const int h{PIC_HEIGH_PX};
    
    const float tmpMin{-10.f};
    const float tmpMax{30.f};
    
    if (telems.size() > 1) {
        if (mLastSec != sec || mLastDur != duration) {
            mVbos.clear();
            
            for (int t{0}; t < telems.size() - 1; ++t) {
                const int tm_shifted{telems.at(t).unixTime - sec};
                const float x1{(float)(int)(PIC_WIDTH_PX * tm_shifted / duration)};
                
                const int tm_shiftedNext = telems.at(t + 1).unixTime - sec;
                const float x2{(float)(int)(PIC_WIDTH_PX * tm_shiftedNext / duration)};
                
                const auto& tel = telems.at(t);
                
                const float mX{fl::map(tel.tmp_solar_mX, tmpMin, tmpMax, 0.2f, 1.8f)};
                const float pX{fl::map(tel.tmp_solar_pX, tmpMin, tmpMax, 0.2f, 1.8f)};
                const float mY{fl::map((tel.tmp_solar_mY1 + tel.tmp_solar_mY2) * 0.5f, tmpMin, tmpMax, 3.f, 7.f)};
                const float pY{fl::map((tel.tmp_solar_pY1 + tel.tmp_solar_pY2) * 0.5f, tmpMin, tmpMax, 3.f, 7.f)};
                const float mZ{fl::map((tel.tmp_solar_mZ1 + tel.tmp_solar_mZ2) * 0.5f, tmpMin, tmpMax, 0.3f, 0.7f)};
                const float pZ{fl::map((tel.tmp_solar_pZ1 + tel.tmp_solar_pZ2) * 0.5f, tmpMin, tmpMax, 6.f, 10.f)};
                
                const int w{(int)(x2 - x1)};
                
                if (w < 1) continue;
                
                auto vbo = make_shared<Vbo>();
                
                __block vector<Vec3f> vertices(w * h);
                __block vector<FloatColor> colors(w * h);
                
                dispatch_queue_t queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
                dispatch_group_t group = dispatch_group_create();
                
                for (int j{0}; j < h; j++) {
                    __block int _j = j;
                    dispatch_group_async(group, queue, ^{
                        for (int i{0}; i < w; i++) {
                            MC::Vector v;
                            MC::Color c;
                            v.x = (i - x1) / (float)PIC_WIDTH_PX;
                            v.y = _j / (float)PIC_HEIGH_PX;
                            v.z = 5.0;
                            c.r = c.g = c.b = 0.5;
                            MC::multicolor(v, &c,
                                           0.7, 2.0, 8.0, 0.2,
                                           mZ, pZ, mY, pY,
                                           mX, pX, 2e4);
                            vertices.at(i + _j * w).set(x1 + i, _j, 0.f);
                            colors.at(i + _j * w).set(c.r, c.g, c.b, 1.f);
                        }
                    });
                }
                
                dispatch_group_notify(group, queue, ^{
                });
                
                dispatch_group_wait(group, DISPATCH_TIME_FOREVER);
                
                vbo->setVertexData(vertices);
                vbo->setColorData(colors);
                mVbos.push_back(vbo);
            }
        }
        
        setColor(Color::white);
        enableColorArray();
        for (auto& v : mVbos)
            v->draw(GL_POINTS);
        disableColorArray();
    }
    
    disableVertexArray();
    
    mLastSec = sec;
    mLastDur = duration;
}

@end