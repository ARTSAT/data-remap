//
//  GLFrameBuffer.m
//  inseparable
//
//  Created by h on 7/8/14.
//  Copyright (c) 2014 h. All rights reserved.
//

#import "GLFrameBuffer.h"

@implementation GLFrameBuffer


-(id)initWithSize:(NSSize)size{


    self = [super init];

    textureSize = size;

    [self initTexture:textureSize];
    [self initRenderbuffer:textureSize];
    [self initFramebuffer:textureSize];

    
    return self;
}

-(void)initTexture:(NSSize)size{


    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

    glGenTextures( 1, &texture_name );
    glBindTexture( GL_TEXTURE_RECTANGLE_EXT, texture_name );
    glTexImage2D( GL_TEXTURE_RECTANGLE_EXT, 0, GL_RGBA, size.width, size.height,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );

    glBindTexture( GL_TEXTURE_RECTANGLE_EXT, 0 );


}


-(void)initRenderbuffer:(NSSize)size{

    glGenRenderbuffersEXT( 1, &renderbuffer_name );
    glBindRenderbufferEXT( GL_RENDERBUFFER_EXT, renderbuffer_name );
    glRenderbufferStorageEXT( GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT,
                             size.width, size.height );

    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);

}

-(void)initFramebuffer:(NSSize)size{

    glGenFramebuffersEXT( 1, &framebuffer_name );
    glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, framebuffer_name );

    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT,
                              GL_COLOR_ATTACHMENT0_EXT,
                              GL_TEXTURE_RECTANGLE_EXT,
                              texture_name,
                              0 );

    glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT,
                                 GL_DEPTH_ATTACHMENT_EXT,
                                 GL_RENDERBUFFER_EXT,
                                 renderbuffer_name );

    glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );
}


-(void)bind{

    //glPushAttrib(GL_VIEWPORT_BIT);
    glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, framebuffer_name );


    glViewport(0, 0, textureSize.width, textureSize.height);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();



}


-(void)unbind{

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glBindFramebuffer(GL_FRAMEBUFFER_EXT, 0);

}

-(void)renderBufferTexture{

    //glShadeModel(GL_FLAT);

    glEnable(GL_TEXTURE_RECTANGLE_EXT);
    glBindTexture(GL_TEXTURE_RECTANGLE_EXT, texture_name);

    glBegin(GL_TRIANGLE_STRIP);

    glTexCoord2f(0, 0);
    glVertex2f(0, textureSize.height);

    glTexCoord2f(textureSize.width, 0);
    glVertex2f(textureSize.width, textureSize.height);

    glTexCoord2f(0, textureSize.height);
    glVertex2f(0, 0);

    glTexCoord2f(textureSize.width, textureSize.height);
    glVertex2f(textureSize.width, 0);

    glEnd();
    glDisable(GL_TEXTURE_RECTANGLE_EXT);
    glBindTexture(GL_TEXTURE_RECTANGLE_EXT, 0);

}


-(void)bindTexture{

    //glShadeModel(GL_FLAT);

    glEnable(GL_TEXTURE_RECTANGLE_EXT);
    glBindTexture(GL_TEXTURE_RECTANGLE_EXT, texture_name);

}

-(void)unbindTexture{
    glDisable(GL_TEXTURE_RECTANGLE_EXT);
    glBindTexture(GL_TEXTURE_RECTANGLE_EXT, 0);

}

-(GLuint)textureID{ return texture_name;    }



-(void)writeToFile:(NSString*)filePath{

    @autoreleasepool {

        int samplesPerPixel = 4;

        int size = (int)textureSize.width * (int)textureSize.height * samplesPerPixel;
        char *data = new char[size];
        glReadPixels(0,0,textureSize.width,textureSize.height,GL_RGBA,GL_UNSIGNED_BYTE,data);

        NSBitmapImageRep *bitmap = [[NSBitmapImageRep alloc]
                                    initWithBitmapDataPlanes:(unsigned char **)&data
                                    pixelsWide:textureSize.width
                                    pixelsHigh:textureSize.height
                                    bitsPerSample:8
                                    samplesPerPixel:samplesPerPixel  // or 4 with alpha
                                    hasAlpha:YES
                                    isPlanar:NO
                                    colorSpaceName:NSDeviceRGBColorSpace
                                    bitmapFormat:0
                                    bytesPerRow:0  // 0 == determine automatically
                                    bitsPerPixel:0];  // 0 == determine automatically


        NSData *pngData = [bitmap representationUsingType:NSPNGFileType properties:nil];
        [pngData writeToFile:[filePath stringByExpandingTildeInPath] atomically:YES];
        
        
    }

}



@end
