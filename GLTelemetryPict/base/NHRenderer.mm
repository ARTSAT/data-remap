//
//  NHRenderer.m
//  GLTelemetryPict
//
//  Created by h on 7/28/15.
//  Copyright (c) 2015 h. All rights reserved.
//

#import "NHRenderer.h"

@implementation NHRenderer



float minAvr = 100;
float maxAvr = 0;

float minX = 100.f;
float maxX = 0.f;
float minY = 100.f;
float maxY = 0.f;
float minZ = 100.f;
float maxZ = 0.f;


-(id)init{

    self = [super init];




    for (int i=0; i<reader->telemetries.size(); ++i) {

        float avr = averageTMPofSolarPanels(reader->telemetries[i]);
        if (avr>=maxAvr)    maxAvr = avr;
        if (avr<minAvr)     minAvr = avr;

        float avrX = averageTMPofSolarPanelX(reader->telemetries[i]);
        if (avrX>=maxX)    maxX = avrX;
        if (avrX<minX)     minX = avrX;

        float avrY = averageTMPofSolarPanelY(reader->telemetries[i]);
        if (avrY>=maxY)    maxY = avrY;
        if (avrY<minY)     minY = avrY;

        float avrZ = averageTMPofSolarPanelZ(reader->telemetries[i]);
        if (avrZ>=maxZ)    maxZ = avrZ;
        if (avrZ<minZ)     minZ = avrZ;

//        NSLog(@"%f",avr);

    }

    NSLog(@"max avr = %f / min avr = %f", maxAvr,minAvr);
    NSLog(@"max X = %f / min X = %f", maxX,minX);
    NSLog(@"max Y = %f / min Y = %f", maxY,minY);
    NSLog(@"max Z = %f / min Z = %f", maxZ,minZ);


    return self;

}





-(void)renderFromUnixTime:(int)sec
                 duration:(int)duration{




    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    vector<telemetry> telems = reader->telemetriesInRange(sec, duration);

    int draw_area_h = 5120;



//    glDisable(GL_BLEND);
//    glColor3f(0, 0, 0);
//    glRectf(0, 0, PIC_WIDTH_PX, draw_area_h);


//    glEnable(GL_BLEND);
//    glBlendAdd();

    glDisable(GL_BLEND);

    if (telems.size() >1) {

        for (int i=0; i<telems.size()-1; ++i) {

            int tm_shifted = telems[i].unixTime - sec;
            float x = PIC_WIDTH_PX * tm_shifted/duration;

            int tm_shiftedNext = telems[i+1].unixTime - sec;
            float x2 = PIC_WIDTH_PX * tm_shiftedNext/duration;


//            glColor3f(0, 0, 0);
//            glBegin(GL_POINTS);
//            for (int s=x; s<x2; s++) {
//                float lim = (averageTMPofSolarPanels(telems[i]) - (minAvr));
//                lim*=32;
//                for (int n=0; n<lim; ++n) {
//                    glVertex2f(s, rand()%draw_area_h);
//                }
//            }
//            glEnd();


            int seed = rand()%3;
            for (int t=0; t<3; ++t) {
                int target = (t+seed)%3;

                [self renderTmpAtX:x to:x2
                             telem:telems[i]
                             areaH:draw_area_h
                              axis:target];
            }

        }
    }


//    glColor3f(1, 1, 1);
//    glBlendReverse();
//    glRectf(0, 0, PIC_WIDTH_PX, draw_area_h);


}

-(void)renderTmpAtX:(int)x
                  to:(int)x2
               telem:(telemetry)telem
               areaH:(int)h
               axis:(int)ax{


    switch (ax) {
        case 0:
            glColor3f(0, 0, 0);
            break;
        case 1:
            glColor3f(0, 0, 0);
            break;
        case 2:
            glColor3f(0, 0, 0);
            break;
        default:
            break;
    }

    glBegin(GL_POINTS);
    for (int s=x; s<x2; s++) {

        float lim;
        switch (ax) {
            case 0:
                 lim = (averageTMPofSolarPanelX(telem) - (minX));
                break;
            case 1:
                 lim = (averageTMPofSolarPanelY(telem) - (minY));
                break;
            case 2:
                 lim = (averageTMPofSolarPanelZ(telem) - (minZ));
                break;
            default:
                break;
        }

        lim*=64;
        for (int n=0; n<lim; ++n) {
            glVertex2f(s, rand()%h);
        }
    }
    glEnd();
}


@end
