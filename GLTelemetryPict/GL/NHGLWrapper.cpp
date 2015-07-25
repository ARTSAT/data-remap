//
//  NHGLWrapper.cpp
//  ssNH
//
//  Created by h on 3/18/14.
//  Copyright (c) 2014 r. All rights reserved.
//


#include "NHGLWrapper.h"

void glBlendAlpha()		{	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	}
void glBlendAdd()		{	glBlendFunc(GL_SRC_ALPHA, GL_ONE);					}
void glBlendMulti()		{	glBlendFunc(GL_ZERO, GL_SRC_COLOR);					}
void glBlendScreen()	{	glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE);		}
void glBlendReverse()	{	glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);		}
void glBlendReverse2()	{	glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);		}


void renderCross( int x, int y, int length){

    float l = length/2.f;

    glBegin(GL_LINES);
    glVertex2f(x-l, y);
    glVertex2f(x+l+1, y);

    glVertex2f(x, y-l-1);
    glVertex2f(x, y+l);

    glEnd();

}




void set2dViewPortFromTop( int w, int h ){
    set2dViewPortFromTop(0, 0, w, h);
}

void set2dViewPortFromTop( int x, int y, int w, int h ){

    glViewport(x,y,w,h);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D(x,x+w,y+h,y);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();


}


void set2dViewPortFromBottom( int w, int h ){
    set2dViewPortFromBottom(0, 0, w, h);
}

void set2dViewPortFromBottom( int x, int y, int w, int h ){

    glViewport(x,y,w,h);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D(x,x+w,y,y+h);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    
    
}