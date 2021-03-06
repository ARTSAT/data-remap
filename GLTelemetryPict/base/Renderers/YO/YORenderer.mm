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
#import "YOBatches.h"
#include "flTinyGLUtils.h"

using namespace YO;

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
//    glClearColor(1, 1, 1, 1);
//    glClear(GL_COLOR_BUFFER_BIT);

    vector<telemetry> telems = reader->telemetriesInRange(sec, duration);
    
    glLineWidth(1);
    glPointSize(1);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    if (telems.size() >1) {
        
        for (int i=0; i<telems.size()-1; ++i) {
            int tm_shifted = telems[i].unixTime - sec;
            float x1 = (int)(PIC_WIDTH_PX * tm_shifted/duration);
            
            int tm_shiftedNext = telems[i+1].unixTime - sec;
            float x2 = (int)(PIC_WIDTH_PX * tm_shiftedNext/duration);
            
            const auto& t1 = telems.at(i+0);
            const auto& t2 = telems.at(i+1);
            
            // -40 to 60
            
            //cout << t1.tmp_solar_mX << ", " << t1.tmp_solar_pX << endl;
            //cout << t1.cur_solar_mX << ", " << t1.cur_solar_pX << endl;
            //cout << t1.magn[0] << endl;
            float tmpMin = -10.f;
            float tmpMax =  30.f;
            float maxCurrent = 80;
            
            //cout << (int)tmx1 << endl;
            
            //cout << (int)cmx1.r << ", " << (int)cmx1.g<< ", " << (int)cmx1.b << endl;
            
            std::vector<Color> colors;
            std::vector<Vertex> vertices;
            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_COLOR_ARRAY);
            //const int step = 4;
            const int step = 4;
            
            const int n = x2 - x1;
            glPushMatrix();
            glTranslatef(0.f, 4000.f, 0.f);
            //glBegin(GL_LINES);

            for (int k=0; k<n; k+=step) {
                const float f = k/(float)n;
                float x = x1 + k;
                float mgn = t1.magn[0] * (1.f - f) + t2.magn[0] * f;
                const float h = 15000.f * fl::map(mgn, 0.f, 360.f, 0.f, 1.f, true);
                float tmx = t1.tmp_solar_mX * (1.f - f) + t2.tmp_solar_mX;
                float tpx = t1.tmp_solar_pX * (1.f - f) + t2.tmp_solar_pX;
                unsigned char _tmx = fl::map(tmx, tmpMin, tmpMax, 0.f, 255.f, true);
                unsigned char _tpx = fl::map(tpx, tmpMin, tmpMax, 0.f, 255.f, true);
                RgbColor cmx = HsvToRgb(HsvColor{_tmx, 255, 255});
                RgbColor cpx = HsvToRgb(HsvColor{_tpx, 255, 255});
                float am = t1.cur_solar_mX * (1.f - f) + t2.cur_solar_mX * f;
                float ap = t1.cur_solar_pX * (1.f - f) + t2.cur_solar_pX * f;
                am = fl::map(am, 0.f, maxCurrent, 0.f, 1.f, true);
                ap = fl::map(ap, 0.f, maxCurrent, 0.f, 1.f, true);
                const int ny = (int)h;
                for (int l=0; l<=ny; l+=step) {
                    const float f2 = l/(float)ny;
                    const float r = (cmx.r/255.f)*(1.f-f2) + (cpx.r/255.f)*f2;
                    const float g = (cmx.g/255.f)*(1.f-f2) + (cpx.g/255.f)*f2;
                    const float b = (cmx.b/255.f)*(1.f-f2) + (cpx.b/255.f)*f2;
                    const float a = am*(1.f-f2) + ap*f2;
                    colors.push_back(Color{r, g, b, a});
                    vertices.push_back(Vertex{x, -h*0.5f+l +1});
                }
                glVertexPointer(3, GL_FLOAT, 0, &vertices.at(0).x);
                glColorPointer(4, GL_FLOAT, 0, &colors.at(0).r);
                //glColor4f(cmx.r/255.f, cmx.g/255.f, cmx.b/255.f, am); glVertex2f(x, -h*0.5f);
                //glColor4f(cpx.r/255.f, cpx.g/255.f, cpx.b/255.f, ap); glVertex2f(x,  h*0.5f);
            }
            glDrawArrays(GL_POINTS, 0, (GLsizei)vertices.size());
            //glEnd();
            glPopMatrix();
            
            colors.clear();
            vertices.clear();
            
            glPushMatrix();
            glTranslatef(0.f, 2000.f, 0.f);
            //glBegin(GL_LINES);
            for (int k=0; k<n; k+=step) {
                const float f = k/(float)n;
                float x = x1 + k;
                float mgn = t1.magn[1] * (1.f - f) + t2.magn[1] * f;
                const float h = 15000.f * fl::map(mgn, 0.f, 360.f, 0.f, 1.f, true);
                float tmx = t1.tmp_solar_mY1 * (1.f - f) + t2.tmp_solar_mY1;
                float tpx = t1.tmp_solar_pY1 * (1.f - f) + t2.tmp_solar_pY1;
                unsigned char _tmx = fl::map(tmx, tmpMin, tmpMax, 0.f, 255.f, true);
                unsigned char _tpx = fl::map(tpx, tmpMin, tmpMax, 0.f, 255.f, true);
                RgbColor cmx = HsvToRgb(HsvColor{_tmx, 255, 255});
                RgbColor cpx = HsvToRgb(HsvColor{_tpx, 255, 255});
                float am = t1.cur_solar_mY1 * (1.f - f) + t2.cur_solar_mY1 * f;
                float ap = t1.cur_solar_pY1 * (1.f - f) + t2.cur_solar_pY1 * f;
                am = fl::map(am, 0.f, maxCurrent, 0.f, 1.f, true);
                ap = fl::map(ap, 0.f, maxCurrent, 0.f, 1.f, true);
                const int ny = (int)h;
                for (int l=0; l<=ny; l+=step) {
                    const float f2 = l/(float)ny;
                    const float r = (cmx.r/255.f)*(1.f-f2) + (cpx.r/255.f)*f2;
                    const float g = (cmx.g/255.f)*(1.f-f2) + (cpx.g/255.f)*f2;
                    const float b = (cmx.b/255.f)*(1.f-f2) + (cpx.b/255.f)*f2;
                    const float a = am*(1.f-f2) + ap*f2;
                    colors.push_back(Color{r, g, b, a});
                    vertices.push_back(Vertex{x, -h*0.5f+l});
                }
                glVertexPointer(3, GL_FLOAT, 0, &vertices.at(0).x);
                glColorPointer(4, GL_FLOAT, 0, &colors.at(0).r);
                //glColor4f(cmx.r/255.f, cmx.g/255.f, cmx.b/255.f, am); glVertex2f(x, -h*0.5f);
                //glColor4f(cpx.r/255.f, cpx.g/255.f, cpx.b/255.f, ap); glVertex2f(x,  h*0.5f);
            }
            glDrawArrays(GL_POINTS, 0, (GLsizei)vertices.size());
            //glEnd();
            glPopMatrix();

            
            glDisableClientState(GL_VERTEX_ARRAY);
            glDisableClientState(GL_COLOR_ARRAY);

//            const float x{(x1 + x2) / 2.f};
//            
//            for (int j=0; j<3; j++) {
//                float r, g, b;
////                switch (j) {
////                    case 0:
////                        r = 1.f; g = 0.f; b = 0.f;
////                        break;
////                    case 1:
////                        r = 0.f; g = 1.f; b = 0.f;
////                        break;
////                    case 2:
////                        r = 0.f; g = 0.f; b = 1.f;
////                        break;
////                    default:
////                        r = 0.f; g = 0.f; b = 0.f;
////                        break;
////                }
//                
//                RgbColor c = HsvToRgb(HsvColor{0, 255, 255});
//                
//                r = c.r/255.f; g = c.g/255.f; b = c.b/255.f;
//                glColor3f(0.f, 0.f, 0.f);
//                
//                glPushMatrix();
//                glTranslatef(x, 0.f, 0.f);
//                glRotatef(t1.magn[j], 0.f, 0.f, 1.f);
//                
//                const float hlen{100.f * t1.gyro[j]};
//                
//                glBegin(GL_LINES);
//                glColor4f(1.f, 1.f, 1.f, 1.f); glVertex2f(-hlen, 0.f);
//                glColor4f(r, g, b, 1.f); glVertex2f(0.f, 0.f);
//                glColor4f(1.f, 1.f, 1.f, 1.f); glVertex2f( hlen, 0.f);
//                glEnd();
//                
//                glPopMatrix();
//            }
//            
        }
    }
    
#ifdef YO_DEBUG
    [mRuler renderFromUnixTime:sec duration:duration];
#endif
}

@end