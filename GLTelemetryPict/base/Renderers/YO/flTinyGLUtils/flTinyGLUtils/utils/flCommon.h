/* port from oF */

//  flCommon.h
//  flTinyGLUtils
//
//  Created by Onishi Yoshito on 10/29/13.
//  Copyright (c) 2013 Onishi Yoshito. All rights reserved.
//

#ifndef __flTinyGLUtils__flCommon__
#define __flTinyGLUtils__flCommon__


//-------------------------------
//  find the system type --------
//-------------------------------

// 		helpful:
// 		http://www.ogre3d.org/docs/api/html/OgrePlatform_8h-source.html

#if defined( __WIN32__ ) || defined( _WIN32 )
#define TARGET_WIN32
#elif defined( __APPLE_CC__)
#include <TargetConditionals.h>

#if (TARGET_OS_IPHONE_SIMULATOR) || (TARGET_OS_IPHONE) || (TARGET_IPHONE)
#define TARGET_IPHONE
#define TARGET_IOS
#define TARGET_OPENGLES
#else
#define TARGET_OSX
#endif
#elif defined (__ANDROID__)
#define TARGET_ANDROID
#define TARGET_OPENGLES
#elif defined(__ARMEL__)
#define TARGET_LINUX
#define TARGET_OPENGLES
#define TARGET_LINUX_ARM
#else
#define TARGET_LINUX
#endif
//-------------------------------


// then the the platform specific includes:
#ifdef TARGET_WIN32
//this is for TryEnterCriticalSection
//http://www.zeroc.com/forums/help-center/351-ice-1-2-tryentercriticalsection-problem.html
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x500
#endif
#define WIN32_LEAN_AND_MEAN

#if (_MSC_VER)
#define NOMINMAX
//http://stackoverflow.com/questions/1904635/warning-c4003-and-errors-c2589-and-c2059-on-x-stdnumeric-limitsintmax
#endif

#include <windows.h>
#define GLEW_STATIC
#include "GL\glew.h"
#include "GL\wglew.h"
#include "glu.h"
#define __WINDOWS_DS__
#define __WINDOWS_MM__
#if (_MSC_VER)       // microsoft visual studio
#include <stdint.h>
#include <functional>
#pragma warning(disable : 4018)		// signed/unsigned mismatch (since vector.size() is a size_t)
#pragma warning(disable : 4068)		// unknown pragmas
#pragma warning(disable : 4101)		// unreferenced local variable
#pragma warning(disable : 4267)		// conversion from size_t to Size warning... possible loss of data
#pragma warning(disable : 4311)		// type cast pointer truncation (qt vp)
#pragma warning(disable : 4312)		// type cast conversion (in qt vp)
#pragma warning(disable : 4800)		// 'Boolean' : forcing value to bool 'true' or 'false'
// warnings: http://msdn.microsoft.com/library/2c8f766e.aspx
#endif

#define TARGET_LITTLE_ENDIAN			// intel cpu

// some gl.h files, like dev-c++, are old - this is pretty universal
#ifndef GL_BGR_EXT
#define GL_BGR_EXT 0x80E0
#endif

// #define WIN32_HIGH_RES_TIMING

// note: this is experimental!
// uncomment to turn this on (only for windows machines)
// if you want to try setting the timer to be high resolution
// this could make camera grabbing and other low level
// operations quicker, but you must quit the app normally,
// ie, using "esc", rather than killing the process or closing
// the console window in order to set the timer resolution back
// to normal (since the high res timer might give the OS
// problems)
// info: http://www.geisswerks.com/ryan/FAQS/timing.html

#endif

#ifdef TARGET_OSX
#ifndef __MACOSX_CORE__
#define __MACOSX_CORE__
#endif
#include <unistd.h>
//#include "GL/glew.h"
#include <OpenGL/gl.h>
#include <ApplicationServices/ApplicationServices.h>

#if defined(__LITTLE_ENDIAN__)
#define TARGET_LITTLE_ENDIAN		// intel cpu
#endif
#endif

#ifdef TARGET_LINUX

#define GL_GLEXT_PROTOTYPES
#include <unistd.h>

#ifdef TARGET_LINUX_ARM
#ifdef TARGET_RASPBERRY_PI
#include "bcm_host.h"
#endif

#include "GLES/gl.h"
#include "GLES/glext.h"
#include "GLES2/gl2.h"
#include "GLES2/gl2ext.h"

#define EGL_EGLEXT_PROTOTYPES
#include "EGL/egl.h"
#include "EGL/eglext.h"
#else // normal linux
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glx.h>
#endif

// for some reason, this isn't defined at compile time,
// so this hack let's us work
// for 99% of the linux folks that are on intel
// everyone one else will have RGB / BGR issues.
//#if defined(__LITTLE_ENDIAN__)
#define TARGET_LITTLE_ENDIAN		// intel cpu
//#endif

// some things for serial compilation:
#define B14400	14400
#define B28800	28800

#endif


#ifdef TARGET_IOS
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>

#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>


#define TARGET_LITTLE_ENDIAN		// arm cpu
#endif

#ifdef TARGET_ANDROID
#include <typeinfo>
#include <unistd.h>
#include <GLES/gl.h>
#define GL_GLEXT_PROTOTYPES
#include <GLES/glext.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#define TARGET_LITTLE_ENDIAN
#endif


#ifndef __MWERKS__
#include <cstdlib>
#endif


#define BUFFER_OFFSET(i) ((char *)NULL + (i))

namespace fl {
    
    enum Attributes
    {
        ATTRIB_VERTEX    = 0,
        ATTRIB_COLOR     = 1,
        ATTRIB_NORMAL    = 2,
        ATTRIB_TEXCOORD  = 3,
        ATTRIB_TANGENT   = 4,
        ATTRIB_POINT_SIZE = 5,
        NUM_ATTRIBUTES,
    };
}

#define FL_NAMESPACE_BEGIN namespace fl {
#define FL_NAMESPACE_END }

#define FL_UNNAMED_NAMESPACE_BEGIN namespace {
#define FL_UNNAMED_NAMESPACE_END }

#define NAMESPACE_BEGIN(name) namespace name {
#define NAMESPACE_END }

#ifndef STRINGIFY
#define STRINGIFY(A)  #A
#endif

#define GLSL_SOURCE(version, shader)  "#version " #version "\n" #shader

#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(bytes) ((GLubyte *)NULL + (bytes))
#endif

#endif /* defined(__flTinyGLUtils__flCommon__) */
