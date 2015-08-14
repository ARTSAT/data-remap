//
//  NHRenderer.m
//  GLTelemetryPict
//
//  Created by h on 7/28/15.
//  Copyright (c) 2015 h. All rights reserved.
//

#import "NHRenderer.h"


#define POINTS


@implementation NHRenderer


//static TestRenderer *ruler;


float minAvr = 100;
float maxAvr = 0;

float minX = 100.f;
float maxX = 0.f;
float minY = 100.f;
float maxY = 0.f;
float minZ = 100.f;
float maxZ = 0.f;

float minBatAvr = 100;
float maxBatAvr = 0;

float minPowerOBCtmp = 100;
float maxPowerOBCtmp = 0;

float minPowerOBCcur = 10000;
float maxPowerOBCcur = -1;



vector<float> rotations[3];


-(id)init{

    self = [super init];

    for (int i=0; i<reader->telemetries.size(); ++i) {

        float avrB = averageTMPofBatteries(reader->telemetries[i]);
        if (avrB>=maxBatAvr)    maxBatAvr = avrB;
        if (avrB<minBatAvr)     minBatAvr = avrB;


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


        float tempPwrOBC = reader->telemetries[i].tmp_powerOBC;
        if (tempPwrOBC>=maxPowerOBCtmp)    maxPowerOBCtmp = tempPwrOBC;
        if (tempPwrOBC<minPowerOBCtmp)     minPowerOBCtmp = tempPwrOBC;


        float curPwrOBC = reader->telemetries[i].cur_powerOBC;
        if (curPwrOBC>=maxPowerOBCcur)    maxPowerOBCcur = curPwrOBC;
        if (curPwrOBC<minPowerOBCcur)     minPowerOBCcur = curPwrOBC;

    }


    rotations[0].push_back(0);
    rotations[1].push_back(0);
    rotations[2].push_back(0);


    float aX,aY,aZ = 0.f;

    for (int i=0; i<reader->telemetries.size()-1; ++i) {

        int tm  = reader->telemetries[i].unixTime;
        int tm2 = reader->telemetries[i+1].unixTime;

        float *rot = reader->telemetries[i].gyro;


        for (int t=tm; t<tm2; t++) {

            float angX = rot[0];
            float angY = rot[1];
            float angZ = rot[2];

            aX += angX;
            aY += angY;
            aZ += angZ;


            rotations[0].push_back( aX );
            rotations[1].push_back( aY );
            rotations[2].push_back( aZ );

        }
    }


    NSLog(@"max avr = %f / min avr = %f", maxAvr,minAvr);
    NSLog(@"max X = %f / min X = %f", maxX,minX);
    NSLog(@"max Y = %f / min Y = %f", maxY,minY);
    NSLog(@"max Z = %f / min Z = %f", maxZ,minZ);

    NSLog(@"max B = %f / min B = %f", maxBatAvr,minBatAvr);

    NSLog(@"powerOBC max  = %f / min = %f", maxPowerOBCtmp,minPowerOBCtmp);
    NSLog(@"powerOBC Cur max  = %f / min = %f", maxPowerOBCcur,minPowerOBCcur);


    unsigned long t = invaderTLE->lastUnixEpoch();

    NSLog(@"last epoch = %lu",t);

    return self;

}

#define LINE (8)//9


-(void)renderFromUnixTime:(int)sec
                 duration:(int)duration{

    glPushMatrix();
    glTranslatef(0, ruler_h, 0);

    int draw_area_h = screen_h;

    vector<telemetry> telems = reader->telemetriesInRange(sec, duration);

    glLineWidth(1);
    glDisable(GL_BLEND);

    if (telems.size() >1) {

        for (int i=0; i<telems.size()-1; ++i) {


            int tm_shifted = telems[i].unixTime - sec;
            float x = PIC_WIDTH_PX * tm_shifted/duration;

            int tm_shiftedNext = telems[i+1].unixTime - sec;
            float x2 = PIC_WIDTH_PX * tm_shiftedNext/duration;


            glPointSize(1);
            int seed = rand()%3;
            for (int t=0; t<3; ++t) {
                int target = (t+seed)%3;

                [self renderTmpAtX:x
                                to:x2
                             telem:telems[i]
                             areaH:draw_area_h
                              axis:target];
            }



            //line
            glDisable(GL_BLEND);
            glColor3f(0,0,0);
            [self renderPowerOBCTmpAtX:x
                                    to:x2
                                 telem:telems[i]
                                 areaH:draw_area_h
                             lineShift:5+2
                                  Line:NO];

            glDisable(GL_BLEND);
            glColor3f(0, 0, 0);
            [self renderPowerOBCCurAtX:x
                                    to:x2
                                 telem:telems[i]
                                 areaH:draw_area_h
                               dotSize:1
                             lineShift:4+2
                                factor:12.f]; //4




            glColor3f(0, 0, 0);
            [self renderBat2:telems[i]
                           x:x to:x2
                           h:draw_area_h
                   lineShift:6+2
                      factor:32.f]; //16.f

            [self renderBat:telems[i]
                           :x
                           :draw_area_h
                  lineShift:6+2];

            [self renderMag:x to:x2 telem:telems[i]];


        }
    }



    [self renderRotation:sec
                duration:duration
                     pit:2400
                     rad:2400];



    #pragma mark TLE
    glDisable(GL_BLEND);
    glPointSize(2);
    glColor3f(0, 0, 0);
    [self renderOrbitLong:sec
                       dur:duration
                       pit:8];//11


    glDisable(GL_BLEND);
    glColor3f(0,0,0);
    glPointSize(2);//2
    [self renderOrbit:sec
                  dur:duration
                  pit:3];




    glPopMatrix();

}



-(void)renderOrbit:(int)sec dur:(int)duration pit:(int)pit{

    float r2        = 2560;
    int marginSec   = (r2/PX_PER_HOUR)*3600;


    glBegin(GL_POINTS);
    for (int unixtm = sec - marginSec; unixtm < sec + duration + marginSec ; unixtm+=pit) {//4

//deorbitUnixTime

        //if (unixtm < reader->lastUnixTime() && unixtm > invaderTLE->firstUnixEpoch() ) {
        if (unixtm < deorbitUnixTime && unixtm > invaderTLE->firstUnixEpoch() ) {
       // if (unixtm < reader->lastUnixTime() && unixtm > invaderTLE->firstUnixEpoch() ) {

            cGeoTime geo = invaderTLE->geometryAtUnixTime( unixtm );


            float lat = geo.LatitudeRad();
            float lon = geo.LongitudeRad();
            float alt = geo.AltitudeKm();//6370.f +

            float y = alt*sinf(lat);
            float xz = alt*cosf(lat);
            float x = xz*cosf(lon);
            float z = xz*sinf(lon);

            float posX = PIC_WIDTH_PX*(float)(unixtm - sec)/(86400.f*DAY_IN_A_PIC);

            glVertex2f(posX + r2*x/400.f,
                       screen_h*.5f + r2*y/400.f );
            
        }
        
        
    }
    glEnd();
    glDisable(GL_BLEND);



}




-(void)renderOrbitLong:(int)sec
                   dur:(int)duration
                   pit:(int)pit{

//    glEnable(GL_BLEND);
//    glBlendFuncSeparate(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA,GL_SRC_ALPHA,GL_ONE); //alpha
//
//    glPointSize(2);
//    glColor4f(0,0,0,1);



    glBegin(GL_POINTS);
    for (double unixtm=sec; unixtm<sec+duration; unixtm+=pit) {//2

        cGeoTime geo = invaderTLE->geometryAtUnixTime(unixtm);

        if (unixtm < deorbitUnixTime && unixtm > invaderTLE->firstUnixEpoch() ) {
//        if (unixtm < reader->lastUnixTime() && unixtm > invaderTLE->firstUnixEpoch() ) {
            float lat = geo.LatitudeRad();
            float lon = geo.LongitudeRad();
            float alt = geo.AltitudeKm();//6370.f +

            float y = alt*sinf(lat);
            float xz = alt*cosf(lat);
            float x = xz*cosf(lon);
            float z = xz*sinf(lon);

            float sin = sinf(lon);
            float r = 1024;//screen_h*.5f;//1024*1.5;//screen_h*.5f;//1024;//1024;

            float posX = PIC_WIDTH_PX*(float)(unixtm - sec)/(86400.f*DAY_IN_A_PIC);
            //glVertex2f(posX, r*sin + PIC_HEIGH_PX - r );
            glVertex2f(posX, r*sin + screen_h*.5f );

        }
    }
    glEnd();

}




-(void)renderBat:(telemetry)telem
                :(int)x
                :(int)height
       lineShift:(int)lineShift{

    float batAvr = averageTMPofBatteries(telem);

    float lim = batAvr - minBatAvr;
    lim*=512;
//
//    if (lim<0) {
//        glColor3f(0, 0, 1);
//    }else{
//        glColor3f(1, 1, 0);
//    }

    glPointSize(1);
    glColor3f(0, 0, 0);

    //glColor3f(1, 1, 0);

    glBegin(GL_POINTS);
    for (int n=0; n<fabsf(lim); ++n) {
        //glVertex2f(x, 36+48 + rand()%(draw_area_h - 36-48));
        glVertex2f(x, rand()%height);
        //glVertex2f(x, (rand()%(draw_area_h)) );
    }
    glEnd();


}




-(void)renderRotation:(int)sec
             duration:(int)duration
                  pit:(int)pit
                  rad:(float)ra{

    int margin = 86400*4;


    glEnable(GL_BLEND);
    glBlendAdd();


    glLineWidth(1);

    glColor3f(1, 1, 1);
    glBegin(GL_LINES);

    for (int unixtm=sec - margin; unixtm<sec+duration + margin; unixtm+=pit) {

        int temp = unixtm - reader->firstUnixTime();
        int temp2 = unixtm - sec;

        float earthSin = sinOfEarthRevolution(unixtm);


        float earthY = 1024.f * earthSin;


        if (temp>=0) {

            for (int i=0; i<3; ++i) {

                float rot = rotations[i][temp];

                float x_base = PIC_WIDTH_PX * temp2/duration;
                float y_base = PIC_HEIGH_PX*.5f;

                float x = x_base + ra*cosf(rot*M_PI/180.f);
                float y = y_base + ra*sinf(rot*M_PI/180.f);

                float x2 = x_base + ra*cosf((rot+180.f)*M_PI/180.f);
                float y2 = y_base + ra*sinf((rot+180.f)*M_PI/180.f);

                glVertex2f(x, y + earthY);
                glVertex2f(x_base, y_base + earthY);
                //glVertex2f(x2, y2);
            }
        }
    }
    glEnd();



    glEnable(GL_BLEND);
    glBlendAdd();

    glColor3f(1, 1, 1);

    for (int i=0; i<3; ++i) {

        glLineWidth(1);
        glBegin(GL_LINE_STRIP);

        for (int unixtm=sec - margin; unixtm<sec+duration + margin; unixtm+=pit) {

            int temp = unixtm - reader->firstUnixTime();
            int temp2 = unixtm - sec;


            if (temp>=0) {

                float rot = rotations[i][temp];

                float x_base = PIC_WIDTH_PX * temp2/duration;
                float y_base = PIC_HEIGH_PX*.5f;

                float x = x_base + ra*cosf(rot*M_PI/180.f);
                float y = y_base + ra*sinf(rot*M_PI/180.f);

                glVertex2f(x, y);
            }
        }
        glEnd();
    }

    glDisable(GL_BLEND);

}




-(void)renderMag:(int)x
              to:(int)x2
           telem:(telemetry)telem{


    float *mag = telem.magn;
    float mx = mag[0];
    float my = mag[1];
    float mz = mag[2];

   // float rad = 5000.f;

    float lon,lat;
    getPolar(mx, my, mz, &lat, &lon);


    float pit = sqrtf(powf(mx, 2.f) + powf(my, 2.f) + powf(mz, 2.f));

    glColor3f(0,0,0);
    glPointSize(1);
    glBegin(GL_POINTS);

//    float y = rad*sinf(lat);
//    float xz = rad*cosf(lat);
//    float z = xz*sinf(lon);
//    float xx = xz*cosf(lon);



    int pitTouse = pit*.2f;//4f;//pit*.04f;
    int numLimit = screen_h/pitTouse;

    for (int s=x; s<x2; s++) {
        //glVertex2f(s - z,   screen_h*.5f - y);
        for (int n=0; n<numLimit; n++) {
            glVertex2f(s, n*pitTouse + s%(pitTouse) );

        }

    }

    glEnd();


}




-(void)renderPowerOBCCurAtX:(int)x
                         to:(int)x2
                      telem:(telemetry)telem
                      areaH:(int)h
                    dotSize:(int)dotsize
                  lineShift:(int)lineShift
                     factor:(float)factor{

    float lim = telem.cur_powerOBC - minPowerOBCcur;
    //lim*=(1.5f);
    lim*=(factor);//8.f


    glPointSize(dotsize);//4



//    glEnable(GL_BLEND);
//    glBlendReverse();
//    glBlendFuncSeparate(GL_ONE_MINUS_DST_COLOR, GL_ZERO, GL_SRC_ALPHA, GL_ONE);
//    glColor4f(1,1,1,1);


    glBegin(GL_POINTS);
    for (int s=x; s<x2; s+=dotsize) {
        for (int n=0; n<lim; ++n) {
            int y = rand()%( h/LINE);
            glVertex2f(s,  y*LINE+lineShift);//6
        }
    }
    glEnd();

    glPointSize(1);
}


-(void)renderBat2:(telemetry)telem
                x:(int)x
               to:(int)x2
                h:(int)height
        lineShift:(int)lineShift
           factor:(float)factor{

    float batAvr = averageTMPofBatteries(telem);

    float lim = batAvr - minBatAvr;
    lim*=factor;//512;

//    if (lim<0) {
//        glColor3f(0, 0, 1);
//    }else{
//        glColor3f(1, 1, 0);
//    }

    glPointSize(1);

    glBegin(GL_POINTS);

    for (int s=x; s<x2; s++) {
        for (int n=0; n<lim; ++n) {

            int y = rand()%( height/LINE);
            glVertex2f(s,  + y*LINE+lineShift);   //lineShift=5

        }
    }
//    for (int n=0; n<fabsf(lim); ++n) {
//        //glVertex2f(x, 36+48 + rand()%(draw_area_h - 36-48));
//        glVertex2f(x, LINE*(rand()%(height/LINE)) + lineShift);
//        //glVertex2f(x, (rand()%(draw_area_h)) );
//    }
    glEnd();
    
    
}





-(void)renderPowerOBCTmpAtX:(int)x
                         to:(int)x2
                      telem:(telemetry)telem
                      areaH:(int)h
                  lineShift:(int)lineShift
                       Line:(BOOL)isLine{

    int length = 4;

    float lim = telem.tmp_powerOBC - minPowerOBCtmp;
    lim*=(64*1);//64




    if (isLine) {
        glLineWidth(1);
        glBegin(GL_LINES);

        for (int s=x; s<x2; s++) {
            for (int n=0; n<lim; ++n) {

                int y = rand()%(h/LINE);

//                glVertex2f(s+length,  + y*LINE+lineShift + length);   //lineShift=5
//                glVertex2f(s-length,  + y*LINE+lineShift - length);

                glVertex2f(s,  + y*LINE+lineShift + length);   //lineShift=5
                glVertex2f(s,  + y*LINE+lineShift);

            }
        }
        glEnd();

    }else{

        glPointSize(1);
        glBegin(GL_POINTS);

        for (int s=x; s<x2; s++) {
            for (int n=0; n<lim; ++n) {

                int y = rand()%( h/LINE );
                glVertex2f(s,  + y*LINE+lineShift);   //lineShift=5
            }
        }
        glEnd();

    }
}




-(void)renderTmpAtX:(int)x
                  to:(int)x2
               telem:(telemetry)telem
               areaH:(int)h
               axis:(int)ax{


    glEnable(GL_BLEND);
    glBlendMulti();


    glColor4f(0, 0, 0,1);

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

        lim*=(32*2);//64
        for (int n=0; n<lim; ++n) {

            int y = rand()%( h /LINE);

            glVertex2f(s,  y*LINE + ax + 2);
        }
    }
    glEnd();

    glDisable(GL_BLEND);

}


@end
