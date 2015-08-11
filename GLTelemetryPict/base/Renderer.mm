//
//  Renderer.m
//  TelemetryPict
//
//  Created by h on 7/17/15.
//  Copyright (c) 2015 h. All rights reserved.
//

#import "Renderer.h"

@implementation Renderer


-(id)init{

    self = [super init];


    //NSString *csvPath = [[[[NSBundle mainBundle] bundlePath] stringByDeletingLastPathComponent] stringByAppendingPathComponent:@"INVADER_telemetry_selected.csv"];
    
    NSString *csvPath = [NSString stringWithFormat:@"../../data/INVADER_telemetry_selected.csv"];


    NSLog(@"open %@",csvPath);
    reader = new telemetryReader([csvPath UTF8String]);

    invaderTLE = new TLEManager();


    timeCodeText = [[charTex alloc] initWithFont:[NSFont fontWithName:@"Helvetica" size:24]
                                       forRetina:NO
                                       antiAlias:YES];

    return self;
}



-(void)renderFromUnixTime:(int)sec
                 duration:(int)duration{

}


@end




@implementation TestRenderer

-(void)renderFromUnixTime:(int)sec
                 duration:(int)duration{

//    glClearColor(1, 1, 1, 1);
//    glClear(GL_COLOR_BUFFER_BIT);


    glLineWidth(1);
    glViewport(0,0,PIC_WIDTH_PX,PIC_HEIGH_PX);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D(0,PIC_WIDTH_PX,0,PIC_HEIGH_PX);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();



    int dayCnount = duration/86400.f;

    NSLog(@"dayCnount %i",dayCnount);

    for (int i=0; i<dayCnount; ++i) {

        time_t t = sec + 86400*i;
        struct tm *tm = localtime(&t);
        char date[32];
        strftime(date, sizeof(date), "%Y/%m/%d %H:%M:%S", tm);
        NSLog(@"%s",date);

        NSString* timeCode = [NSString stringWithFormat:@"%i/%02i/%02i",tm->tm_year+1900,tm->tm_mon+1,tm->tm_mday];


        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//alpha

        glColor4f(0, 0, 0, 1);
        glPushMatrix();
        glTranslatef(4 + PX_PER_DAY*i, 0, 0);

        [timeCodeText renderString:timeCode];

        glPopMatrix();
        glDisable(GL_BLEND);

        glBegin(GL_LINES);
        glVertex2f(1+PX_PER_DAY*i, 0);
        glVertex2f(1+PX_PER_DAY*i, screen_h);
        glEnd();


    }


    glBegin(GL_LINES);
    glVertex2f(0, 36);
    glVertex2f(screen_w, 36);

    glVertex2f(0, 36+48);
    glVertex2f(screen_w, 36+48);


    glVertex2f(0, 1);
    glVertex2f(screen_w, 1);



    glEnd();

//    for (int i=0; i<duration; i+=PX_PER_HOUR*6 ) {
//
//        glBegin(GL_LINES);
//        glVertex2f(i, 36);
//        glVertex2f(i, 36 + 8);
//        glVertex2f(i, 36+48);
//        glVertex2f(i, 36+48 - 8);
//
//        glEnd();
//
//
//    }



    vector<telemetry> telemsInTerm = reader->telemetriesInRange( sec , duration);

    for (int i=0; i<telemsInTerm.size(); ++i) {

        //int time = telemsInAday[i].unixTime - reader->firstUnixTime() - sec;
        int time = telemsInTerm[i].unixTime - sec;

        float interm = (float)time/(86400.f*DAY_IN_A_PIC);
        interm*=PIC_WIDTH_PX;

        glColor3f(0,0,0);
        glBegin(GL_LINES);
        glVertex2f(interm, 36);
        glVertex2f(interm, 36+48);
        glEnd();

    }

    
}



@end