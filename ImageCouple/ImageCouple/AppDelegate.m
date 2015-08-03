//
//  AppDelegate.m
//  ImageCouple
//
//  Created by h on 7/28/15.
//  Copyright (c) 2015 h. All rights reserved.
//

#import "AppDelegate.h"


#define DPI             (180.f)


@interface AppDelegate ()

@property (weak) IBOutlet NSWindow *window;
@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {


    @autoreleasepool {

        NSString *targetDir = [@"~/Desktop/imgs/" stringByExpandingTildeInPath];

        NSFileManager *man = [NSFileManager defaultManager];
        NSArray *files = [man contentsOfDirectoryAtPath:targetDir error:nil];

        NSMutableArray *pngPathes = [NSMutableArray array];

        int pngCnt = 0;
        for ( NSString * name in files) {
            if ([[name pathExtension] isEqualToString:@"png"]) {
                NSString *fullPath = [targetDir stringByAppendingPathComponent:name];
                NSLog(@"%@",fullPath);
                pngCnt++;
                [pngPathes addObject:fullPath];
            }
        }

        NSLog(@"%i png files, %lu",pngCnt,[pngPathes count]);


        //get image size
        NSImage *tmp = [[NSImage alloc] initWithContentsOfFile:pngPathes[0]];

        float w = [tmp size].width;
        float h = [tmp size].height;

        NSLog(@"%f x %f",w,h);


        NSImage *dstImage = [[NSImage alloc] initWithSize:NSMakeSize(w * pngCnt, h)];

        int cnt = 0;
        for ( NSString* pathes in pngPathes) {

            @autoreleasepool {
                NSImage *target = [[NSImage alloc] initWithContentsOfFile:pathes];

                [dstImage lockFocus];

                [target drawAtPoint:NSMakePoint(cnt*w, 0)
                           fromRect:NSMakeRect(0, 0, w, h)
                          operation:1
                           fraction:1];


                [dstImage unlockFocus];
                cnt++;
            }
        }




        NSBitmapImageRep *bmpImgRep = [NSBitmapImageRep imageRepWithData:[dstImage TIFFRepresentation]];
        float factor = 72.f/DPI;
        [bmpImgRep setSize:NSMakeSize(w*pngCnt*factor, h*factor)];


        NSData *pngData = [bmpImgRep representationUsingType:NSPNGFileType properties:nil];
        [pngData writeToFile:[@"~/Desktop/allTelemetries.png" stringByExpandingTildeInPath] atomically:YES];

    }


    [NSApp terminate:self];



}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}

@end
