//
//  NHRenderer.m
//  GLTelemetryPict
//
//  Created by h on 7/28/15.
//  Copyright (c) 2015 h. All rights reserved.
//

#import "NHRenderer.h"




@implementation NHRenderer


static TestRenderer *ruler;


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



vector<float> rotations[3];


-(id)init{

    self = [super init];





    ruler = [TestRenderer new];



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

//        NSLog(@"%f",avr);

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

            //NSLog(@"%f,%f,%f",aX,aY,aZ);

        }

    }



    NSLog(@"max avr = %f / min avr = %f", maxAvr,minAvr);
    NSLog(@"max X = %f / min X = %f", maxX,minX);
    NSLog(@"max Y = %f / min Y = %f", maxY,minY);
    NSLog(@"max Z = %f / min Z = %f", maxZ,minZ);

    NSLog(@"max B = %f / min B = %f", maxBatAvr,minBatAvr);


    return self;

}





-(void)renderFromUnixTime:(int)sec
                 duration:(int)duration{




    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    vector<telemetry> telems = reader->telemetriesInRange(sec, duration);

    int draw_area_h = 5120*1.f;



//    glEnable(GL_BLEND);
//    glBlendAdd();

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

                [self renderTmpAtX:x to:x2
                             telem:telems[i]
                             areaH:draw_area_h
                              axis:target];
            }


            float batAvr = averageTMPofBatteries(telems[i]);

            float lim = batAvr;// - minBatAvr;
            lim*=256;

            if (lim<0) {
                glColor3f(0, 0, 1);
            }else{
                glColor3f(1, 1, 0);
            }



            glBegin(GL_POINTS);
            for (int n=0; n<fabsf(lim); ++n) {
                glVertex2f(x, 0 + 36+48 + rand()%(draw_area_h - 36-48));
            }
            glEnd();




//            int targetTm = telems[i].unixTime;
//            cGeoTime geo = invaderTLE->geometryAtUnixTime(targetTm);
//
//            float lat = geo.LatitudeRad();
//            float lon = geo.LongitudeRad();
//            float alt = geo.AltitudeKm();//6370.f +
//
//            float y = alt*sinf(lat);
//            float xz = alt*cosf(lat);
//            float xx = xz*cosf(lon);
//            float z = xz*sinf(lon);
//
//            float posX = PIC_WIDTH_PX*(float)(targetTm - sec)/(86400.f*DAY_IN_A_PIC);

            float tobc = telems[i].tmp_powerOBC;
            float tobc2 = telems[i+1].tmp_powerOBC;

            //NSLog(@"%f",tobc);

            glColor3f(1, 0, 0);
            glLineWidth(2);
            glBegin(GL_LINES);

            glVertex2f(x,  5120-tobc*160.f );
            glVertex2f(x2, 5120-tobc2*160.f );

            glEnd();



        }
    }



    [self renderRotation:sec duration:duration];


//    glColor3f(1, 1, 1);
//    glBlendReverse();
//    glRectf(0, 0, PIC_WIDTH_PX, draw_area_h);


    glEnable(GL_BLEND);
    //glBlendAlpha();
    glBlendFuncSeparate(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA,GL_SRC_ALPHA,GL_ONE); //alpha

    glEnable(GL_LINE_SMOOTH);





    glLineWidth(5);
    glColor4f(0, 0, 0,.45);
    glBegin(GL_LINE_STRIP);
    for (int unixtm=sec; unixtm<sec+duration; unixtm+=60) {

        cGeoTime geo = invaderTLE->geometryAtUnixTime(unixtm);


        float lat = geo.LatitudeRad();
        float lon = geo.LongitudeRad();
        float alt = geo.AltitudeKm();//6370.f +

        float y = alt*sinf(lat);
        float xz = alt*cosf(lat);
        float x = xz*cosf(lon);
        float z = xz*sinf(lon);

        float sin = sinf(lon);
        float r = 1024;

        float posX = PIC_WIDTH_PX*(float)(unixtm - sec)/(86400.f*DAY_IN_A_PIC);
        //glVertex2f(posX, r*sin + PIC_HEIGH_PX - r );
        glVertex2f(posX, r*sin + PIC_HEIGH_PX*.5f );
        
    }
    glEnd();



    float r2        = 2560;
    int marginSec   = (r2/PX_PER_HOUR)*3600;

    NSLog(@"marginSec = %i",marginSec);


    glColor4f(1, 1, 1,1);
    //glColor4f(0,0,0,.25);
    glLineWidth(2);
    glBegin(GL_LINE_STRIP);
    //for (int unixtm = sec - marginSec; unixtm < sec + duration + marginSec ; unixtm+=60) {
    for (int unixtm = sec - marginSec; unixtm < sec + duration ; unixtm+=60) {


        cGeoTime geo = invaderTLE->geometryAtUnixTime( unixtm );


        float lat = geo.LatitudeRad();
        float lon = geo.LongitudeRad();
        float alt = geo.AltitudeKm();//6370.f +

        float y = alt*sinf(lat);
        float xz = alt*cosf(lat);
        float x = xz*cosf(lon);
        float z = xz*sinf(lon);

        float posX = PIC_WIDTH_PX*(float)(unixtm - sec)/(86400.f*DAY_IN_A_PIC);



        glVertex2f(posX + r2*x/400.f, PIC_HEIGH_PX*.5f + r2*y/400.f );

    }
    glEnd();
    glDisable(GL_LINE_SMOOTH);



    glLineWidth(1);
    [ruler renderFromUnixTime:sec duration:duration];








}



-(void)renderRotation:(int)sec
             duration:(int)duration{



    int margin = 86400*4;


    glLineWidth(1);
    glBegin(GL_LINES);
    for (int unixtm=sec - margin; unixtm<sec+duration + margin; unixtm+=3600) {


        int temp = unixtm - reader->firstUnixTime();
        int temp2 = unixtm - sec;


        if (temp>=0) {


            for (int i=0; i<3; ++i) {



                if (i==0) {
                    glColor3f(1, 0, 0);
                }else if(i==1){
                    glColor3f(0, 1, 0);
                }else{
                    glColor3f(0, 0, 1);
                }

                float rot = rotations[i][temp];

                float x_base = PIC_WIDTH_PX * temp2/duration;
                float y_base = PIC_HEIGH_PX*.5f;

                float ra = 2400;

                float x = x_base + ra*cosf(rot*M_PI/180.f);
                float y = y_base + ra*sinf(rot*M_PI/180.f);


                float x2 = x_base + ra*cosf((rot+180.f)*M_PI/180.f);
                float y2 = y_base + ra*sinf((rot+180.f)*M_PI/180.f);
                
                glVertex2f(x, y);
                glVertex2f(x2, y2);
                
            }
            
            
        }
        
    }
    glEnd();


}





-(void)renderTmpAtX:(int)x
                  to:(int)x2
               telem:(telemetry)telem
               areaH:(int)h
               axis:(int)ax{


    switch (ax) {
        case 0:
            glColor4f(0, 0, 0,1);
            break;
        case 1:
            glColor4f(0, 0, 0,1);
            break;
        case 2:
            glColor4f(0, 0, 0,1);
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

        lim*=48;//64
        for (int n=0; n<lim; ++n) {
            glVertex2f(s, 36+48 + rand()%(h - 36-48));
        }
    }
    glEnd();
}


@end
