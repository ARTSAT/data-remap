//
//  flGLProps.h
//  workYO
//
//  Created by YoshitoONISHI on 6/8/15.
//  Copyright (c) 2015 r. All rights reserved.
//

#ifndef __workYO__flGLProps__
#define __workYO__flGLProps__

#include "flCommon.h"
#include "flColor.h"
#include "flGraphics.h"
#include "flVec3f.h"

FL_NAMESPACE_BEGIN

enum BlendMode {
    BLEND_DISABLED,
    BLEND_ALPHA,
    BLEND_ADD,
    BLEND_MULTIPLY,
    BLEND_SCREEN,
    BLEND_INVERT,
#ifndef TARGET_OPENGLES
    BLEND_SUBTRACT,
#endif
};

struct ScopedBlending {
    ScopedBlending(BlendMode mode);
    virtual ~ScopedBlending();
    
};

void enableBlend(BlendMode mode);
void disableBlend();

struct ScopedColor {
    ScopedColor(const Color& color);
    ScopedColor(const FloatColor& color);
    ScopedColor(const Color& color, float alpha);
    ScopedColor(const FloatColor& color, float alpha);
    ScopedColor(float w, float a = 1.f);
    ScopedColor(float r, float g, float b, float a = 1.f);
    
    virtual ~ScopedColor();
};

void clear(float w, float a = 1.f);
void clear(float r, float g, float b, float a = 1.f);

void setColor(const Color& color);
void setColor(const FloatColor& color);
void setColor(const Color& color, float alpha);
void setColor(const FloatColor& color, float alpha);
void setColor(float w, float a = 1.f);
void setColor(float r, float g, float b, float a = 1.f);


struct ScopedMatrix {
    ScopedMatrix() { glPushMatrix(); };
    virtual ~ScopedMatrix() { glPopMatrix(); }
};

struct ScopedTranslate : public ScopedMatrix {
    ScopedTranslate(const Vec3f& v) { translate(v); };
    ScopedTranslate(float x, float y, float z = 0.f) { translate(x, y, z); };
    virtual ~ScopedTranslate() {}
};

struct ScopedScale : public ScopedMatrix {
    ScopedScale(float sx, float sy, float sz) { scale(sx, sy, sz); };
    ScopedScale(float s) { scale(s); };
    virtual ~ScopedScale() {}
};

struct ScopedRotate : public ScopedMatrix {
    ScopedRotate(float angle, float x, float y, float z)
    {
        glRotatef(angle, x, y, z);
    };
    
    virtual ~ScopedRotate() {}
};

class Matrix4x4;

void makeScreenPerspective(Matrix4x4* perspective,
                           Matrix4x4* lookat,
                           int w,
                           int h,
                           float fov = 60.f,
                           float nearDist = 0.f,
                           float farDist = 0.f,
                           bool flip = true);

void makeScreenOrtho(Matrix4x4* ortho,
                     float width,
                     float height,
                     float nearDist = -1.f,
                     float farDist = 1.f);

int glhProjectf(float objx,
                float objy,
                float objz,
                float *modelview,
                float *projection,
                int *viewport,
                float *windowCoordinate);

int glhUnProjectf(float winx,
                  float winy,
                  float winz,
                  float *modelview,
                  float *projection,
                  int *viewport,
                  float *objectCoordinate);

void billboard(Matrix4x4* mat, bool flattenScale = true);

struct ScopedLineWidth {
    ScopedLineWidth(float w);
    virtual ~ScopedLineWidth();
};

struct ScopedPointSize {
    ScopedPointSize(float s);
    virtual ~ScopedPointSize();
};


#ifndef TARGET_OPENGLES
void billboard(bool normalizeScale = true);
void loadPersiectiveMatrix(float w,
                           float h,
                           float fov = 60.f,
                           float nearDist = 0.f,
                           float farDist = 0.f,
                           bool flip = true);
void loadOrthoMatrix(float w,
                     float h,
                     float nearDist = -1.f,
                     float farDist = -1.f);
#endif

FL_NAMESPACE_END

#endif /* defined(__workYO__flGLProps__) */
