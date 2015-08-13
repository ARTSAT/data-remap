//
//  Renderer.m
//  TelemetryPict
//
//  Created by h on 7/17/15.
//  Copyright (c) 2015 h. All rights reserved.
//

#import "Renderer.h"



NSString* monthStr( int mon ){

    NSString *month;

    switch (mon) {
        case 1:
            month = @"Jan";
            break;
        case 2:
            month = @"Feb";
            break;
        case 3:
            month = @"Mar";
            break;
        case 4:
            month = @"Apr";
            break;
        case 5:
            month = @"May";
            break;
        case 6:
            month = @"Jun";
            break;
        case 7:
            month = @"Jul";
            break;
        case 8:
            month = @"Aug";
            break;
        case 9:
            month = @"Sep";
            break;
        case 10:
            month = @"Oct";
            break;
        case 11:
            month = @"Nov";
            break;
        case 12:
            month = @"Dec";
            break;

        default:
            break;
    }

    return month;
}


@implementation Renderer


-(id)init{

    self = [super init];


    //NSString *csvPath = [[[[NSBundle mainBundle] bundlePath] stringByDeletingLastPathComponent] stringByAppendingPathComponent:@"INVADER_telemetry_selected.csv"];
    
    NSString *csvPath = [NSString stringWithFormat:@"../../data/INVADER_telemetry_selected.csv"];


    NSLog(@"open %@",csvPath);
    reader = new telemetryReader([csvPath UTF8String]);

    invaderTLE = new TLEManager();


    deorbitUnixTime = unixTimeFromDate(2014, 9, 2, 9, 47, 0) - 9*3600;

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



-(id)init{
    self = [super init];

    smallFont = [[charTex alloc] initWithFont:[NSFont fontWithName:@"Helvetica" size:12]
                                    forRetina:NO
                                    antiAlias:YES];

    return self;
}





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

        int mon = tm->tm_mon+1;
        NSString *month = monthStr(mon);

        NSString* timeCode = [NSString stringWithFormat:@"%02i %@ %02i",tm->tm_mday,month,tm->tm_year+1900];


        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//alpha

        glColor4f(0, 0, 0, 1);
        glPushMatrix();
        glTranslatef(4 + PX_PER_DAY*i, 3, 0);

        [timeCodeText renderString:timeCode];

        glPopMatrix();
        glDisable(GL_BLEND);

        glBegin(GL_LINES);
        glVertex2f(1+PX_PER_DAY*i, 0);
        glVertex2f(1+PX_PER_DAY*i, PIC_HEIGH_PX);
        glEnd();


    }


    glBegin(GL_LINES);
    glVertex2f(0, 36);
    glVertex2f(screen_w, 36);

    glVertex2f(0, 36+24);
    glVertex2f(screen_w, 36+24);


    glVertex2f(0, 36+24+24);
    glVertex2f(screen_w, 36+24+24);

    glVertex2f(0, 1);
    glVertex2f(screen_w, 1);
    glEnd();


    //hours
    int len = 3;
    for (int i=0; i<duration; i+=PX_PER_HOUR ) {

        int hour = (i/PX_PER_HOUR)%24;

        if((i/PX_PER_HOUR)%6==0){

            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//alpha
            glColor4f(0, 0, 0, 1);
            glPushMatrix();
            glTranslatef(i+2, 36+12-8, 0);
            [smallFont renderString:[NSString stringWithFormat:@"%02i",hour]];

            glPopMatrix();
            glDisable(GL_BLEND);


            len = 24;

        }else{
            len = 6;
        }

        glBegin(GL_LINES);
        glVertex2f(i+1, 36+24);
        glVertex2f(i+1, 36+24 - len);

        glEnd();
    }


    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    for (int i=sec; i<sec+duration; i+=10 ) {
        bool visible = invaderTLE->isVisible(i);

        float tm = i - sec;
        float x = PIC_WIDTH_PX*(float)tm/(float)(PX_PER_HOUR*dayCnount*24);

        if (visible) {
            glVertex2f(x, 0);
            glVertex2f(x, 100);

        }




    }
    glEnd();


    vector<telemetry> telemsInTerm = reader->telemetriesInRange( sec , duration);

    for (int i=0; i<telemsInTerm.size(); ++i) {

        //int time = telemsInAday[i].unixTime - reader->firstUnixTime() - sec;
        int time = telemsInTerm[i].unixTime - sec;

        float interm = (float)time/(86400.f*DAY_IN_A_PIC);
        interm*=PIC_WIDTH_PX;

        glColor3f(0,0,0);
        glBegin(GL_LINES);
        glVertex2f(interm, 36+24);
        glVertex2f(interm, 36+48);
        glEnd();

    }

    
}



@end