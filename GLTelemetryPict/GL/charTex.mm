//
//  charTex.mm
//  Typingmonkeys_vol2_12
//
//  Created by user on 11/09/22.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "charTex.h"


@implementation charTex

-(id)initWithFont:(NSFont*)font
        forRetina:(BOOL)retina
        antiAlias:(BOOL)smoothing{


    self = [super init];

    isRetina = retina;

    [self setUpWithFont:font antiAlias:smoothing];

    return self;
    
    
    
}


-(void)setUpWithFont:(NSFont*)font antiAlias:(BOOL)smoothing{

    NSLog(@"charTex setUp Begin");

    NSAttributedString	*atstring;
    NSImage				*image;
    NSBitmapImageRep	*bitmap;
    NSSize framesize;
    NSSize texSize;

    NSMutableDictionary *stanStringAttrib	= [NSMutableDictionary dictionary];

    [stanStringAttrib setObject:font
                         forKey:NSFontAttributeName];

    [stanStringAttrib setObject:[NSColor colorWithDeviceRed:0.f green:0.f blue:0.f alpha:0.f]
                         forKey:NSBackgroundColorAttributeName];


    [stanStringAttrib setObject:[NSColor colorWithDeviceRed:1.f green:1.f blue:1.f alpha:1.f]
                         forKey:NSForegroundColorAttributeName];


    [stanStringAttrib setObject:[NSNumber numberWithFloat:0]
                         forKey:NSKernAttributeName];



    //---
    [stanStringAttrib setObject:[NSNumber numberWithFloat:-2.]
                         forKey:NSStrokeWidthAttributeName];


    [stanStringAttrib setObject:[NSColor colorWithDeviceRed:1.f green:1.f blue:1.f alpha:.6f]
                         forKey:NSStrokeColorAttributeName];




    //NSStrokeWidthAttributeName





    base = glGenLists(255);

    char t;
    char c[] = "a";
    for(unsigned char i=0;i<255;i++){

        t = i;
        strncpy(c, &t,1);
        atstring = [[NSAttributedString alloc] initWithString:[NSString stringWithFormat:@"%s",c]
                                                   attributes:stanStringAttrib];

        framesize = [atstring size];

        if (isRetina) {
            sizes[i] = NSMakeSize(framesize.width*2.f,framesize.height*2.f);
        }else{
            sizes[i] = NSMakeSize(framesize.width,framesize.height);
        }



        if (sizes[i].width>0 && sizes[i].height>0) {

            //[[NSGraphicsContext currentContext] setShouldAntialias:  smoothing ];

            image = [[NSImage alloc] initWithSize:framesize];
            [image lockFocus];

            [[NSGraphicsContext currentContext] setShouldAntialias:  smoothing ];


            [[NSColor colorWithDeviceRed:0.f green:0.f blue:0.f alpha:0.f] set];
            NSRectFill (NSMakeRect (0.0f, 0.0f, framesize.width, framesize.height));
            [atstring drawAtPoint:NSMakePoint(0, 0)];


            if (isRetina) {
                bitmap = [[NSBitmapImageRep alloc] initWithFocusedViewRect:NSMakeRect (0.0f, 0.0f, framesize.width*2.f, framesize.height*2.f)];
            }else{
                bitmap = [[NSBitmapImageRep alloc] initWithFocusedViewRect:NSMakeRect (0.0f, 0.0f, framesize.width, framesize.height)];
            }

            [image unlockFocus];

            texSize.width = [bitmap size].width;
            texSize.height = [bitmap size].height;

            glPushAttrib(GL_ENABLE_BIT);
            glEnable(GL_TEXTURE_RECTANGLE_EXT);
            glGenTextures (1, &textures[i]);
            glBindTexture (GL_TEXTURE_RECTANGLE_EXT, textures[i]);
            glPixelStorei(GL_UNPACK_ALIGNMENT,   1   );

            glTexParameteri(GL_TEXTURE_RECTANGLE_EXT,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            glTexParameteri(GL_TEXTURE_RECTANGLE_EXT,GL_TEXTURE_MIN_FILTER,GL_LINEAR);



            if (isRetina) {
                glTexImage2D (GL_TEXTURE_RECTANGLE_EXT, 0, GL_RGBA, texSize.width*2.f, texSize.height*2.f, 0, GL_RGBA, GL_UNSIGNED_BYTE, [bitmap bitmapData]);
            }else{
                glTexImage2D (GL_TEXTURE_RECTANGLE_EXT, 0, GL_RGBA, texSize.width, texSize.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, [bitmap bitmapData]);
            }


            glDisable(GL_TEXTURE_RECTANGLE_EXT);


            glEnable(GL_TEXTURE_RECTANGLE_EXT);
            glNewList(base + i, GL_COMPILE);
            {
                glBindTexture (GL_TEXTURE_RECTANGLE_EXT, textures[i]);
                glBegin(GL_QUADS);
                glTexCoord2f(0, 0);								glVertex2f(0, 0);
                glTexCoord2f(0, sizes[i].height);				glVertex2f(0, sizes[i].height);
                glTexCoord2f(sizes[i].width, sizes[i].height);	glVertex2f(0+sizes[i].width, sizes[i].height);
                glTexCoord2f(sizes[i].width, 0);				glVertex2f(0+sizes[i].width, 0);
                glEnd();
                
            }
            glEndList();
            glDisable(GL_TEXTURE_RECTANGLE_EXT);
            
            
        }
        //2¥22 NSLog(@"%f %f %f %f",sizes[i].width, sizes[i].height,framesize.width, framesize.height);
        
    }
    
    
    NSLog(@"charTex initialized");
    
}



-(void)renderCString:(char*)c_str{

    int n = strlen(c_str);////[str length];
//    const char *c = [str UTF8String];

    for(int i=0;i<n;++i){
        glCallList((GLuint)(c_str[i]) + base);
        glTranslatef(sizes[c_str[i]].width, 0, 0);
    }

}

-(void)renderString:(NSString*)str{

    glEnable(GL_TEXTURE_RECTANGLE_EXT);

	int n = [str length];
	const char *c = [str UTF8String];
	for(int i=0;i<n;++i){
		glCallList((GLuint)(c[i]) + base);
		glTranslatef(sizes[c[i]].width, 0, 0);
	}

    glDisable(GL_TEXTURE_RECTANGLE_EXT);
    
}

-(void)renderString:(NSString*)str
		 withLength:(int)leng{

	int n = [str length];
	const char *c = [str UTF8String];
	
	for(int i=0;i<n;++i){
		if(i<leng){
			glCallList((GLuint)(c[i]) + base);
		}else {
			glColor3f(0,0,0);
			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_RECTANGLE_EXT);
			glCallList((GLuint)(c[i]) + base);
			glEnable(GL_TEXTURE_RECTANGLE_EXT);
		}

		glTranslatef(sizes[c[i]].width, 0, 0);
	}	
}

-(float)getHeight{
	return sizes[0].height;
}

-(float)getWidth:(NSString*)str{

	int n			= [str length];
	const char *c	= [str UTF8String];
	float tw		= 0.f;
	
	for(int i=0;i<n;++i){
		tw+=sizes[c[i]].width;
	}
	
	return tw;
}

-(float)getWidthOfChar:(char)ch{

//    int n			= [str length];
//    const char *c	= [str UTF8String];
//    float tw		= 0.f;

//    for(int i=0;i<n;++i){
//        tw+=sizes[ c[i] ].width;
//    }
    
    return sizes[ ch ].width;;
}




@end
