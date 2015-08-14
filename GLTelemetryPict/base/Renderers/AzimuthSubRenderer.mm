//
//  AzimuthSubRenderer.m
//  GLTelemetryPict
//
//  Created by Koichiro Mori on 2015/08/14.
//  Copyright (c) 2015年 h. All rights reserved.
//

#import "AzimuthSubRenderer.h"

@implementation AzimuthSubRenderer


-(id)init {
    self = [super init];
    offsetY = PIC_HEIGH_PX * 0.5f + ruler_h;
    
    //NSString *path = [[[[NSBundle mainBundle] bundlePath] stringByDeletingLastPathComponent] stringByAppendingPathComponent:@"INVADER_azimuth.csv"];
    
    NSString *path = [NSString stringWithFormat:@"../../data/INVADER_azimuth.csv"];
    
    telemetry_az = new telemetryReaderAzimuth([path UTF8String]);
    
    return self;
};


-(void)renderFromUnixTime:(int)sec duration:(int)duration {
    
    float scaleFact = 10.0;
    
    vector<telemetryAzimuth> telemsInTerm = self->telemetry_az->telemetriesInRangeAz(sec , duration);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glPushMatrix();
    
    glTranslatef(0, offsetY, 0);
    
    for (int i=0; i<telemsInTerm.size(); ++i) {
        int time = telemsInTerm[i].unixTime - sec;
        
        float interm = (float)time/(86400.f*DAY_IN_A_PIC);
        interm*=PIC_WIDTH_PX;
        
        glPushMatrix();
        glTranslatef(interm, 0, 0);

        glColor4f(1.0,0.0,0.0,1.0);
        [self drawRect:0 y_:0 width: telemsInTerm[i].altitude * scaleFact * sin(telemsInTerm[i].azimuth * 3.145 /180) height:telemsInTerm[i].altitude * scaleFact *-cos(telemsInTerm[i].azimuth * 3.145 /180)];
        
        glPopMatrix();
    }
    
    glPopMatrix();
}


-(void)drawRect:(float)x_ y_:(float)y_ width:(float)width height:(float)height {
    glBegin(GL_LINE_LOOP);
    glVertex2f(0 + x_, 0 + y_);
    glVertex2f(0 + x_ + width, 0 + y_);
    glVertex2f(0 + x_ + width, 0 + y_ + height);
    glVertex2f(0 + x_, 0 + y_ + height);
    glEnd();
};

@end

