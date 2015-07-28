//
//  Controller.m
//  GL
//
//  Created by h on 6/26/15.
//  Copyright (c) 2015 h. All rights reserved.
//

#import "Controller.h"

@implementation Controller



static float viewScale;


const int secInDay = 86400;
float numberOfDay;
//int pictureWidth;

//int _startUnixTime;
//int _endUnixTime;



static telemetryReader * reader;

-(id)init{

    self = [super init];

    [self setup];

    viewScale = 1.f;
    [self fitToScreen];

    targetRenderer = [[RENDERER_CLASS alloc] init];
    azimuthRanderer = [[AzimuthRenderer alloc] init]; // mori
    nh = [NHRenderer new];


    reader = targetRenderer->reader;
    

//    _startUnixTime  = startUnixTime;
//    _endUnixTime    = unixTimeFromDate(2014, 9, 3, 0, 0, 0);

    unsigned long displayDuration = endUnixTime - startUnixTime;
    NSLog(@"displayDuration = %lu sec = %f days",displayDuration,displayDuration/(float)secInDay);

//    pictureWidth = PX_PER_HOUR*24;
//    NSLog(@"%i px width for 24 hours",pictureWidth);

    numberOfDay = displayDuration/(float)secInDay;
    NSLog(@"%f days in total",numberOfDay);

    

    time_t t = reader->firstUnixTime();
    struct tm *tm = localtime(&t);
    char date[32];
    strftime(date, sizeof(date), "%Y/%m/%d %H:%M:%S", tm);
    NSLog(@"%s",date);



    NSLog(@"%i colmuns",TLM_ELEM_COUNT);


    t = reader->lastUnixTime();
    tm = localtime(&t);
    strftime(date, sizeof(date), "%Y/%m/%d %H:%M:%S", tm);
    NSLog(@"%s",date);


    [self changeRenderingTargetTime:nil];


    return self;

}



-(void)setup{

    NSRect screenRect = NSMakeRect(0, 0, screen_w, screen_h);
    
    glView      = [[NHGLView alloc] initWithFrame:screenRect];
    fbo         = [[GLFrameBuffer alloc] initWithSize:NSMakeSize(screen_w, screen_h)];
    fsWindow    = [[NSWindow alloc] initWithContentRect:screenRect
                                           styleMask:NSBorderlessWindowMask
                                             backing:NSBackingStoreBuffered
                                               defer:NO];

    [fsWindow setContentView:glView];
    [fsWindow orderFront: self ];
    [fsWindow setLevel:NSNormalWindowLevel];
}




-(void)renderGL:(int)secStart
       duration:(int)duration
          index:(int)index
         export:(BOOL)needExport{


    [[glView openGLContext] makeCurrentContext];

    [fbo bind];
    {
        glClearColor(1, 1, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        [nh renderFromUnixTime:secStart duration:duration]; // mori
        [targetRenderer renderFromUnixTime:secStart duration:duration];
        [azimuthRanderer renderFromUnixTime:secStart duration:duration]; // mori

        
        if (needExport) {

            NSFileManager *fn = [NSFileManager defaultManager];
            if ( ! [fn fileExistsAtPath:[@"~/Desktop/imgs" stringByExpandingTildeInPath]]) {
                [fn createDirectoryAtPath:[@"~/Desktop/imgs" stringByExpandingTildeInPath]
              withIntermediateDirectories:NO attributes:nil error:nil];
            }

            NSString *fileName = [[NSString  stringWithFormat:@"~/Desktop/imgs/test_%03i.png",index] stringByExpandingTildeInPath];
            [fbo writeToFile:fileName];
        }

    }
    [fbo unbind];


    glClearColor(0.1, 0.1, 0.1, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    set2dViewPortFromBottom(screen_w, screen_h);
    glPushMatrix();
    {
        glScalef(viewScale, viewScale, 1.f);
        glColor3f(1, 1, 1);
        [fbo renderBufferTexture];
    }
    glPopMatrix();

    [[glView openGLContext] flushBuffer];

}




-(void)renderContents{

    set2dViewPortFromTop(screen_w, screen_h);
    glColor4f(1, 1, 1,1);
    glBegin(GL_LINES);
    glVertex2d(0, 0);
    glVertex2d(screen_w, screen_h);
    glEnd();
}




-(IBAction)toggleFit:(id)sender{

    if (viewScale == 1.f) {
        [self fitToScreen];
    }else{
        [self fitToOriginalSize];
    }


    [self changeRenderingTargetTime:nil];
}


-(void)fitToScreen{

    NSRect mainRect = [[NSScreen mainScreen] visibleFrame];

    viewScale = mainRect.size.height/(float)screen_h;

    [fsWindow setFrame:mainRect display:YES];
    [glView setFrameOrigin:NSMakePoint(0, 0)];

    NSLog(@"%f",mainRect.size.height);
}


-(void)fitToOriginalSize{

    int y = [[NSScreen mainScreen] visibleFrame].size.height - screen_h;

    NSRect rect = NSMakeRect(0, y, screen_w, screen_h);

    viewScale = 1.f;
    [fsWindow setFrame:rect display:YES];
    [glView setFrameOrigin:NSMakePoint(0, 0)];
}



-(IBAction)exportPNGs:(id)sender{

    for (int d = 0; d<=numberOfDay; d+=DAY_IN_A_PIC) {

        int start = d*secInDay + startUnixTime;
        int duration = secInDay*DAY_IN_A_PIC;

        [self renderGL:start
              duration:duration
                 index:d/DAY_IN_A_PIC
                export:YES];
    }


}

-(IBAction)changeRenderingTargetTime:(id)sender{

    int day = [sender floatValue];

    int start = day*secInDay + startUnixTime;
    int duration = secInDay*DAY_IN_A_PIC;

    [self renderGL:start
          duration:duration
             index:-1
            export:NO];

    [indexLabel setFloatValue:[sender floatValue]];

}


- (void)calcFPS{

    static int fpsCounter = 0;
    static CFAbsoluteTime fpsTimeStamp;
    fpsCounter++;

    CFAbsoluteTime now = CFAbsoluteTimeGetCurrent();
    if (now - fpsTimeStamp >= 1.f) {

        NSLog(@"%.2f fps",fpsCounter / (now - fpsTimeStamp));

        fpsTimeStamp = now;
        fpsCounter = 0;
    }
}




@end
