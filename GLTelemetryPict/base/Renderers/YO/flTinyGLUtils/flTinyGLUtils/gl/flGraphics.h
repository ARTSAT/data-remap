//
//  flGraphics.h
//  JINS MEME GL Dev
//
//  Created by YoshitoONISHI on 5/16/15.
//  Copyright (c) 2015 YoshitoONISHI. All rights reserved.
//

#ifndef __JINS_MEME_GL_Dev__flGraphics__
#define __JINS_MEME_GL_Dev__flGraphics__

#include "flCommon.h"
#include "flVec3f.h"
#include "flColor.h"

FL_NAMESPACE_BEGIN

class Rectangle;
class Texture;

enum DrawRectMode {
    DRAW_RECT_CENTER,
    DRAW_RECT_CORNER,
};

void setAlign(bool align);
bool getAlign();

struct ScopedAlign {
    ScopedAlign(bool align) : mLastAlign(getAlign()) { setAlign(align); }
    virtual ~ScopedAlign() { setAlign(mLastAlign); }
private:
bool mLastAlign;
};

float aligned(float f);

template<class FL_VEC>
void align(std::vector<FL_VEC>& verts)
{
    for (int i=0; i<verts.size(); i++) {
        for (int j=0; j<FL_VEC::DIM; j++) {
            verts.at(i)[j] = aligned(verts.at(i)[j]);
        }
    }
}

void setUseAttribArray(bool bUse);
bool getUseAttribArray();

void enableVertexArray();
void disableVertexArray();

void enableTexCoordArray();
void disableTexCoordArray();

void enableColorArray();
void disableColorArray();

void setFill(bool fill);
bool getFill();

struct ScopedFill {
    ScopedFill(bool fill) : mLastFill(getFill()) { setFill(fill); }
    virtual ~ScopedFill() { setFill(mLastFill); }
private:
    bool mLastFill;
};

void drawLine(float x, float y);
void drawLine(float x0, float y0, float x1, float y1);
void drawLine(fl::Vec3f v);
void drawLine(fl::Vec3f v0, fl::Vec3f v1);

void drawVertices(const std::vector<fl::Vec2f>& verts);
void drawVertices(const std::vector<fl::Vec3f>& verts);

void drawCircle(float radius);
void drawCircle(float x, float y, float radius);
void drawArc(float radius, float from, float to); // in degrees
void drawArc(float x, float y, float radius, float from, float to);

void drawPointsArc(float radius, float from, float to, int nVerts);
void drawRing(float radius, float width);

void loadNormalizedTexCoords();
void loadTexCoords(float x, float y, float w, float h);
void loadTexCoords(float w, float h);
void loadTexCoords(const Rectangle& r);

void drawRect(float w, float h);
void drawRect(float x, float y, float w, float h);

void drawTexture(const Texture& tex);
void drawTexture(const Texture& tex, float x, float y);
void drawTexture(const Texture& tex, float x, float y, float scale);
void drawTexture(const Texture& tex, float x, float y, float w, float h);

void setDrawVerticesMode(GLenum mode);
GLenum getDrawVerticesMode();

struct ScopedDrawVerticesMode {
    ScopedDrawVerticesMode(GLenum m) : mLastMode(getDrawVerticesMode()) { setDrawVerticesMode(m); }
    virtual ~ScopedDrawVerticesMode() { setDrawVerticesMode(mLastMode); }
private:
    GLenum mLastMode;
};

void setDrawCircleResolution(int res);

void setRectMode(DrawRectMode mode);
DrawRectMode getRectMode();

struct ScopedDrawRectMode {
    ScopedDrawRectMode(DrawRectMode m) : mLastMode(getRectMode()) { setDrawVerticesMode(m); }
    virtual ~ScopedDrawRectMode() { setRectMode(mLastMode); }
private:
    DrawRectMode mLastMode;
};


void setTextureTarget(GLenum target);
GLenum getTextureTarget();

struct ScopedTextureTarget {
    ScopedTextureTarget(GLenum m) : mLastTarget(getTextureTarget()) { setTextureTarget(m); }
    virtual ~ScopedTextureTarget() { setTextureTarget(mLastTarget); }
private:
    GLenum mLastTarget;
};

template<GLsizei DIM>
void loadVertices(const float *verts)
{
    if (getUseAttribArray()) {
        glVertexAttribPointer(fl::ATTRIB_VERTEX,
                              DIM,
                              GL_FLOAT,
                              GL_FALSE,
                              sizeof(float) * DIM,
                              &verts);
    }
    else {
        glVertexPointer(DIM, GL_FLOAT, sizeof(float) * DIM, verts);
    }
}

template<GLsizei DIM>
void loadTexCoords(const float *verts)
{
    if (getUseAttribArray()) {
        glVertexAttribPointer(fl::ATTRIB_TEXCOORD,
                              DIM,
                              GL_FLOAT,
                              GL_FALSE,
                              sizeof(float) * DIM,
                              &verts);
    }
    else {
        glTexCoordPointer(DIM, GL_FLOAT, sizeof(float) * DIM, verts);
    }
}

void loadColors(const float* colors);
void loadColors(const std::vector<fl::Vec4f>& colors);
void loadColors(const std::vector<fl::FloatColor>& colors);

#ifndef TARGET_OPENGLES
void translate(Vec3f p);
void translate(float x, float y, float z = 0.f);
void scale(float s);
void scale(float sx, float sy, float sz);
#endif

FL_NAMESPACE_END

#endif /* defined(__JINS_MEME_GL_Dev__flGraphics__) */
