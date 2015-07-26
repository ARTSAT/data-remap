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
    offsetY = 400;
    
    
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
        
        //int time = telemsInAday[i].unixTime - reader->firstUnixTime() - sec;
        int time = telemsInTerm[i].unixTime - sec;
        
        float interm = (float)time/(86400.f*DAY_IN_A_PIC);
        interm*=PIC_WIDTH_PX;
        
        glColor3f(0,0,0);
        glPushMatrix();
            glTranslatef(interm, 0, 0);
            [self drawCircle:0 cy:0 r:4 num_segments:32];
        
        glPopMatrix();
    
        glPushMatrix();
            glTranslatef(interm, 0, 0);
            PointAzimuth from, to;
            from.x = from.y = to.x = 0.0;
            to.y = 120.0;
            [self drawLine:from to:to rot:telemsInTerm[i].azimuth];
        cout << from.x << to.y << endl;
        glPopMatrix();
        
    }
    
    glPopMatrix();
};

-(void)drawLine:(PointAzimuth)from to:(PointAzimuth)to rot:(float)rot {
    //glRotatef(rot, 0, 0, 1);
    glBegin(GL_LINE);
        glVertex2d(from.x,from.y);
        glVertex2d(to.x,to.y);
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