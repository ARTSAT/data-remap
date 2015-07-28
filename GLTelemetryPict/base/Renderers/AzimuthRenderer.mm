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
    offsetY = PIC_HEIGH_PX*.5f;
    
    //NSString *path = [[[[NSBundle mainBundle] bundlePath] stringByDeletingLastPathComponent] stringByAppendingPathComponent:@"INVADER_azimuth.csv"];
    
    NSString *path = [NSString stringWithFormat:@"../../data/INVADER_azimuth.csv"];
    
    telemetry_az = new telemetryReaderAzimuth([path UTF8String]);
    
    return self;
};

-(void)renderFromUnixTime:(int)sec duration:(int)duration {
    
    float scaleFact = 2.5;
    
    vector<telemetryAzimuth> telemsInTerm = telemetry_az->telemetriesInRangeAz(sec , duration);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glPushMatrix();
    
    glTranslatef(0, self->offsetY, 0);
    
    for (int i=0; i<telemsInTerm.size(); ++i) {
        int time = telemsInTerm[i].unixTime - sec;
        
        float interm = (float)time/(86400.f*DAY_IN_A_PIC);
        interm*=PIC_WIDTH_PX;
        
        glPushMatrix();
            glTranslatef(interm, 0, 0);
            PointAzimuth from, to;
            from.x = from.y = to.x = 0.0;
            to.y = telemsInTerm[i].altitude * scaleFact;
            glPushMatrix();
                glColor4f(0.75,0.75,1.0, 0.8);
                [self drawLine:from to:to rot:telemsInTerm[i].azimuth];
            glPopMatrix();
            glPushMatrix();
                glColor3f(0,255,255);
                //[self drawLine:from to:to rot:telemsInTerm[i].settingAzimuth];
            glPopMatrix();
        glPopMatrix();
        
        //glColor4f(0.2,0.2,0.2,0.75);
        glColor4f(1,0.2,0.2,0.75);
        glPushMatrix();
        glTranslatef(interm, 0, 0);
        
        //[self drawArc:0 y:0 r:telemsInTerm[i].altitude * 2.0 start_angle: telemsInTerm[i].azimuth * 3.145 /180 d_angle: telemsInTerm[i].settingAzimuth * 3.145 /180 segments:64];
        
        [self drawRect:0 y_:0 width: telemsInTerm[i].altitude * scaleFact * sin(telemsInTerm[i].azimuth * 3.145 /180) height:telemsInTerm[i].altitude * scaleFact *-cos(telemsInTerm[i].azimuth * 3.145 /180)];
        
        glPopMatrix();
    }
    
    glPopMatrix();
};

-(void)drawLine:(PointAzimuth)from to:(PointAzimuth)to rot:(float)rot {
    glRotatef(rot + 180, 0, 0, 1);
    glBegin(GL_LINES);
        glVertex2f(from.x,from.y);
        glVertex2f(to.x,to.y);
    glEnd();
}

-(void)drawRect:(float)x_ y_:(float)y_ width:(float)width height:(float)height {
    glBegin(GL_LINE_LOOP);
        glVertex2f(0 + x_, 0 + y_);
        glVertex2f(0 + x_ + width, 0 + y_);
        glVertex2f(0 + x_ + width, 0 + y_ + height);
        glVertex2f(0 + x_, 0 + y_ + height);
    glEnd();
}

-(void)drawCircle:(float)cx cy:(float)cy r:(float)r num_segments:(int)num_segments {
    glBegin(GL_LINE_LOOP);
    for(int i =0; i <= num_segments; i++) {
        double angle = 2 * 3.1415926 * i / num_segments;
        double x = cos(angle) * r + cx;
        double y = sin(angle) * r + cy;
        glVertex2d(x,y);
    }
    glEnd();
};

-(void)drawArc :(float) _x  y:(float) _y r:(float)_r start_angle:(float) start_angle d_angle:(float)d_angle segments:(int)segments {

    float theta = d_angle / float(segments - 1); //<-wrang!!!!!!!!
    float tangetial_factor = tan(theta);
    float radial_factor = cos(theta);

    float x = _r * cos(start_angle);
    float y = _r * sin(start_angle);

    //glRotatef(-270, 0, 0, 1);
    glBegin(GL_LINE_STRIP);
    for(int ii = 0; ii < segments; ii++) {
        glVertex2d(x + _x, y + _y);
        
        float tx = -y;
        float ty = x; 
        
        x += tx * tangetial_factor; 
        y += ty * tangetial_factor; 
        
        x *= radial_factor; 
        y *= radial_factor; 
    } 
    glEnd(); 
}

@end