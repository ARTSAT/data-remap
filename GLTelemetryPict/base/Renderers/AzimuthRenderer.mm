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
    offsetY = 1400;
    return self;
};

-(void)renderFromUnixTime:(int)sec duration:(int)duration {
    
    vector<telemetry> telemsInTerm = reader->telemetriesInRange( sec , duration);
    
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
        
    }
    
    glPopMatrix();
};

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