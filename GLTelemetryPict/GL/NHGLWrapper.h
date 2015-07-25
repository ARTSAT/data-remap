//
//  NHGLWrapper.h
//  ssNH
//
//  Created by h on 3/18/14.
//  Copyright (c) 2014 r. All rights reserved.
//

#ifndef __ssNH__NHGLWrapper__
#define __ssNH__NHGLWrapper__



//#include <iostream>
//#import <GLKit/GLKit.h>
#import <OpenGL/glu.h>
#import <OpenGL/gl.h>
#import <OpenGL/OpenGL.h>

#include <math.h>


void glBlendAlpha();
void glBlendAdd();
void glBlendMulti();
void glBlendScreen();
void glBlendReverse();
void glBlendReverse2();



void set2dViewPortFromTop( int w, int h );
void set2dViewPortFromTop( int x, int y, int w, int h );
void set2dViewPortFromBottom( int w, int h );
void set2dViewPortFromBottom( int x, int y, int w, int h );

void renderCross( int x, int y, int length);


class p3 {

public:

    float px,py,pz;

    p3(float x, float y, float z){
        px = x;
        py = y;
        pz = z;
    }


    ~p3(){
    }


    void setFromPolarCoord( float lat, float lon, float rad ){

        static float mpi = 3.1415926/180.f;
        float xz;

        xz = rad*cosf(lat*mpi);

        py = rad*sinf(lat*mpi);
        px = xz*cosf(lon*mpi);
        pz = xz*sinf(lon*mpi);
    }

};





#endif /* defined(__ssNH__NHGLWrapper__) */
