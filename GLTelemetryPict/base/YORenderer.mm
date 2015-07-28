//
//  YORenderer.m
//  GLTelemetryPict
//
//  Created by YoshitoONISHI on 7/28/15.
//  Copyright (c) 2015 h. All rights reserved.
//

//#define YO_DEBUG

#import <Foundation/Foundation.h>
#import "YORenderer.h"
#import "NHRenderer.h"

@interface YORenderer() {
#ifdef YO_DEBUG
    TestRenderer* mRuler;
#endif
}
@end

@implementation YORenderer

-(id)init
{
    if ((self = [super init])) {
#ifdef YO_DEBUG
        mRuler = [TestRenderer new];
#endif
    }
    return self;
}

-(void)renderFromUnixTime:(int)sec
                 duration:(int)duration
{
    const float y{500.f};
    
//    glClearColor(1, 1, 1, 1);
//    glClear(GL_COLOR_BUFFER_BIT);

    vector<telemetry> telems = reader->telemetriesInRange(sec, duration);
    
    glLineWidth(1);
    glDisable(GL_BLEND);
    
    glPushMatrix();
    glTranslatef(0.f, y, 0.f);
    
    if (telems.size() >1) {
        
        for (int i=0; i<telems.size()-1; ++i) {
            int tm_shifted = telems[i].unixTime - sec;
            float x1 = PIC_WIDTH_PX * tm_shifted/duration;
            
            int tm_shiftedNext = telems[i+1].unixTime - sec;
            float x2 = PIC_WIDTH_PX * tm_shiftedNext/duration;
            
            const auto& t = telems.at(i);
            
            //cout << t.gyro[0] << ", " << t.gyro[1] << ", " << t.gyro[2] << endl;
            
            const float x{(x1 + x2) / 2.f};
            
            for (int j=0; j<3; j++) {
                float r, g, b;
//                switch (j) {
//                    case 0:
//                        r = 1.f; g = 0.f; b = 0.f;
//                        break;
//                    case 1:
//                        r = 0.f; g = 1.f; b = 0.f;
//                        break;
//                    case 2:
//                        r = 0.f; g = 0.f; b = 1.f;
//                        break;
//                    default:
//                        r = 0.f; g = 0.f; b = 0.f;
//                        break;
//                }
                r = 0.f; g = 0.f; b = 0.f;
                glColor3f(0.f, 0.f, 0.f);
                
                glPushMatrix();
                glTranslatef(x, 0.f, 0.f);
                glRotatef(t.magn[j], 0.f, 0.f, 1.f);
                
                const float hlen{100.f * t.gyro[j]};
                
                glBegin(GL_LINES);
                glColor4f(1.f, 1.f, 1.f, 1.f); glVertex2f(-hlen, 0.f);
                glColor4f(r, g, b, 1.f); glVertex2f(0.f, 0.f);
                glColor4f(1.f, 1.f, 1.f, 1.f); glVertex2f( hlen, 0.f);
                glEnd();
                
                glPopMatrix();
            }
            
        }
    }
    
    glPopMatrix();
    
#ifdef YO_DEBUG
    [mRuler renderFromUnixTime:sec duration:duration];
#endif
}

@end