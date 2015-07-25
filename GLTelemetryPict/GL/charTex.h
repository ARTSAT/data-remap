//
//  charTex.h
//  Typingmonkeys_vol2_12
//
//  Created by user on 11/09/22.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <OpenGL/gl.h>

//#import "define.h"


@interface charTex : NSObject {

	
	GLuint textures[256];
	NSSize sizes[256];	
	
@public
	GLuint base;
    BOOL isRetina;
	
	
}


-(id)initWithFont:(NSFont*)font
        forRetina:(BOOL)retina
        antiAlias:(BOOL)smoothing;


-(void)setUpWithFont:(NSFont*)font
           antiAlias:(BOOL)smoothing;


-(void)renderString:(NSString*)str;

-(void)renderCString:(char*)c_str;

-(void)renderString:(NSString*)str
		 withLength:(int)leng;

-(float)getWidth:(NSString*)str;
-(float)getHeight;
-(float)getWidthOfChar:(char)ch;
@end
