//
//  AzimuthRenderer.mm
//  GLTelemetryPict
//
//  Created by Koichiro Mori on 2015/07/26.
//  Copyright (c) 2015年 h. All rights reserved.
//

#import "AzimuthRenderer.h"

@implementation AzimuthRenderer

-(id)init {
    self = [super init];
    offsetY = 900;
    
    
    //NSString *path = [[[[NSBundle mainBundle] bundlePath] stringByDeletingLastPathComponent] stringByAppendingPathComponent:@"INVADER_azimuth.csv"];
    
    NSString *path = [NSString stringWithFormat:@"../../data/INVADER_azimuth.csv"];
    
    telemetry_az = new telemetryReaderAzimuth([path UTF8String]);
    
    return self;
};

-(void)renderFromUnixTime:(int)sec duration:(int)duration {
    
    vector<telemetryAzimuth> telemsInTerm = telemetry_az->telemetriesInRangeAz(sec , duration);
    
    glPushMatrix();
    
    glTranslatef(0, self->offsetY, 0);
    
    for (int i=0; i<telemsInTerm.size(); ++i) {
        int time = telemsInTerm[i].unixTime - sec;
        
        float interm = (float)time/(86400.f*DAY_IN_A_PIC);
        interm*=PIC_WIDTH_PX;
        
        glColor3f(0,0,0);
        glPushMatrix();
            glTranslatef(interm, 0, 0);
            [self drawCircle:0 cy:0 r:telemsInTerm[i].altitude * 2.0 num_segments:64];
        
        glPopMatrix();

        glColor3f(0,0,255);
        glPushMatrix();
            glTranslatef(interm, 0, 0);
            PointAzimuth from, to;
            from.x = from.y = to.x = 0.0;
            to.y = telemsInTerm[i].altitude * 2.0;
            glPushMatrix();
                [self drawLine:from to:to rot:telemsInTerm[i].azimuth];
            glPopMatrix();
        glPopMatrix();
        
    }
    
    glPopMatrix();
};

-(void)drawLine:(PointAzimuth)from to:(PointAzimuth)to rot:(float)rot {
    glRotatef(rot, 0, 0, 1);
    glBegin(GL_LINES);
        glVertex2f(from.x,from.y);
        glVertex2f(to.x,to.y);
    glEnd();
}

-(void)drawCircle:(float)cx cy:(float)cy r:(float)r num_segments:(int)num_segments {
    glBegin(GL_LINE_LOOP);
    for(int i =0; i <= num_segments; i++){
        double angle = 2 * 3.1415926 * i / num_segments;
        double x = cos(angle) * r + cx;
        double y = sin(angle) * r + cy;
        glVertex2d(x,y);
    }
    glEnd();
};

@end