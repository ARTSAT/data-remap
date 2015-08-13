//
//  flGraphics.cpp
//  JINS MEME GL Dev
//
//  Created by YoshitoONISHI on 5/16/15.
//  Copyright (c) 2015 YoshitoONISHI. All rights reserved.
//

#include "flGraphics.h"
#include "flShader.h"
#include "flMath.h"
#include "flVec2f.h"
#include "flVec3f.h"
#include "flEasing.h"
#include "flRectangle.h"
#include "flTexture.h"
#include <vector>

FL_NAMESPACE_BEGIN

#ifdef TARGET_OPENGLES
static bool _useAttribArray = true;
#else
static bool _useAttribArray = false;
#endif

static DrawRectMode _drawRectMode = DRAW_RECT_CORNER;
static int _drawCircleResolution = 64;
static GLenum _drawVerticesMode = GL_LINES;

static bool _isEnabledTexCoords = false;

static bool _fill = true;
static bool _align = false;

static GLenum _textureTarget = GL_TEXTURE_2D;

#pragma mark ___________________________________________________________________
float aligned(float f)
{
    return ::floorf(f) + 0.5f;
}

void setAlign(bool align)
{
    _align = align;
}

bool getAlign()
{
    return _align;
}
//
//void align(std::vector<Vec3f>& verts)
//{
//    for (int i=0; i<verts.size(); i++) {
//        verts.at(i).x = aligned(verts.at(i).x);
//        verts.at(i).y = aligned(verts.at(i).y);
//        verts.at(i).z = aligned(verts.at(i).z);
//    }
//}

#pragma mark ___________________________________________________________________
void setUseAttribArray(bool bUse)
{
    _useAttribArray = bUse;
}

bool getUseAttribArray()
{
    return _useAttribArray;
}

void enableVertexArray()
{
    if (_useAttribArray)
        glEnableVertexAttribArray(fl::ATTRIB_VERTEX);
    else
        glEnableClientState(GL_VERTEX_ARRAY);
}

void disableVertexArray()
{
    if (_useAttribArray)
        glDisableVertexAttribArray(fl::ATTRIB_VERTEX);
    else
        glDisableClientState(GL_VERTEX_ARRAY);
}

void enableTexCoordArray()
{
    if (_useAttribArray)
        glEnableVertexAttribArray(fl::ATTRIB_TEXCOORD);
    else
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    _isEnabledTexCoords = true;
}

void disableTexCoordArray()
{
    if (_useAttribArray)
        glDisableVertexAttribArray(fl::ATTRIB_TEXCOORD);
    else
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    _isEnabledTexCoords = false;
}

void enableColorArray()
{
    if (_useAttribArray)
        glEnableVertexAttribArray(fl::ATTRIB_COLOR);
    else
        glEnableClientState(GL_COLOR_ARRAY);
}

void disableColorArray()
{
    if (_useAttribArray)
        glDisableVertexAttribArray(fl::ATTRIB_COLOR);
    else
        glDisableClientState(GL_COLOR_ARRAY);
}

#pragma mark ___________________________________________________________________
void setFill(bool fill)
{
    _fill = fill;
}

bool getFill()
{
    return _fill;
}

#pragma mark ___________________________________________________________________
void drawLine(float x, float y)
{
    drawLine(0.f, 0.f, x, y);
}

void drawLine(float x0, float y0, float x1, float y1)
{
    if (getAlign()) {
        x0 = aligned(x0);
        y0 = aligned(y0);
        x1 = aligned(x1);
        y1 = aligned(y1);
    }
    const float data[4] = { x0, y0, x1, y1 };
    loadVertices<2>(data);
    glDrawArrays(GL_LINES, 0, 2);
}

void drawLine(fl::Vec3f v)
{
    drawLine(fl::Vec3f::zero(), v);
}

void drawLine(fl::Vec3f v0, fl::Vec3f v1)
{
    if (getAlign()) {
        v0.x = aligned(v0.x);
        v0.y = aligned(v0.y);
        v0.z = aligned(v0.z);
        v1.x = aligned(v1.x);
        v1.y = aligned(v1.y);
        v1.z = aligned(v1.z);
    }
    const float data[6] = { v0.x, v0.y, v0.z, v1.x, v1.y, v1.z };
    loadVertices<3>(data);
    glDrawArrays(GL_LINES, 0, 2);
}

void drawVertices(const std::vector<fl::Vec2f>& verts)
{
    loadVertices<2>(&verts.at(0).x);
    glDrawArrays(_drawVerticesMode, 0, (GLsizei)verts.size());
}

void drawVertices(const std::vector<fl::Vec3f>& verts)
{
    loadVertices<3>(&verts.at(0).x);
    glDrawArrays(_drawVerticesMode, 0, (GLsizei)verts.size());
}

#pragma mark ___________________________________________________________________
void drawCircle(float radius)
{
    drawCircle(0.f, 0.f, radius);
}

void drawCircle(float x, float y, float radius)
{
    std::vector<fl::Vec2f> verts;
    verts.clear();
    if (getFill()) {
        verts.push_back(fl::Vec2f(x, y));
    }
    const float step = TWO_PI/(float)_drawCircleResolution;
    for (int i=0; i<=_drawCircleResolution; i++) {
        const float vx = x + ::cosf(i * step) * radius;
        const float vy = y + ::sinf(i * step) * radius;
        verts.push_back(fl::Vec2f(vx, vy));
    }
    loadVertices<2>(&verts.at(0).x);
    if (getFill())
        glDrawArrays(GL_TRIANGLE_FAN, 0, (GLsizei)verts.size());
    else
        glDrawArrays(GL_LINE_LOOP, 0, (GLsizei)verts.size());
}

void drawArc(float radius, float from, float to)
{
    drawArc(0.f, 0.f, radius, from, to);
}

void drawArc(float x, float y, float radius, float from, float to)
{
    std::vector<fl::Vec2f> verts;
    verts.clear();
    if (getFill()) {
        verts.push_back(fl::Vec2f(x, y));
    }
    for (int i=0; i<=_drawCircleResolution; i++) {
        const float r0 = from + to / (float)_drawCircleResolution * i;
        const float r1 = from + to / (float)_drawCircleResolution * (i+1);
        const float x0 = x + ::cosf(r0 * DEG_TO_RAD) * radius;
        const float y0 = y + ::sinf(r0 * DEG_TO_RAD) * radius;
        const float x1 = x + ::cosf(r1 * DEG_TO_RAD) * radius;
        const float y1 = y + ::sinf(r1 * DEG_TO_RAD) * radius;
        verts.push_back(fl::Vec2f(x0, y0));
        verts.push_back(fl::Vec2f(x1, y1));
    }
    loadVertices<2>(&verts.at(0).x);
    if (getFill())
        glDrawArrays(GL_TRIANGLE_FAN, 0, (GLsizei)verts.size());
    else
        glDrawArrays(GL_LINE_STRIP, 0, (GLsizei)verts.size());
}

void drawPointsArc(float radius, float from, float to, int nVerts)
{
    std::vector<fl::Vec2f> verts(nVerts);
    for (int i=0; i<nVerts; i++) {
        float s = (i-nVerts/2.f)/(float)(nVerts/2.f);
        const float center = (from + (to - from)* 0.5f);
        const float t = (to - from) * 0.5f * s;
        const float x = ::cosf((center + t) * DEG_TO_RAD) * radius;
        const float y = ::sinf((center + t) * DEG_TO_RAD) * radius;
        verts.at(i).set(x, y);
    }
    loadVertices<2>(&verts.at(0).x);
    glDrawArrays(GL_POINTS, 0, nVerts);
}

void drawRing(float radius, float width)
{
    const int numVerts = (_drawCircleResolution + 1) * 2;
    std::vector<fl::Vec2f> verts(numVerts);
    const float step = TWO_PI/(float)_drawCircleResolution;
    
    for (int i=0; i<_drawCircleResolution + 1; i++) {
        const float x0 = ::cosf(i * step) * (radius - width * 0.5f);
        const float y0 = ::sinf(i * step) * (radius - width * 0.5f);
        const float x1 = ::cosf(i * step) * (radius + width * 0.5f);
        const float y1 = ::sinf(i * step) * (radius + width * 0.5f);
        verts.at(i * 2 + 0).set(x0, y0);
        verts.at(i * 2 + 1).set(x1, y1);
    }
    loadVertices<2>(&verts.at(0).x);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, numVerts);
}

#pragma mark ___________________________________________________________________
static std::vector<Vec2f> _tc(6);

void loadNormalizedTexCoords()
{
    loadTexCoords(0.f, 0.f, 1.f, 1.f);
}

void loadTexCoords(float x, float y, float w, float h)
{
    if (getFill()) {
        _tc.at(0).set(x,   y);
        _tc.at(1).set(x+w, y);
        _tc.at(2).set(x+w, y+h);
        _tc.at(3).set(x+w, y+h);
        _tc.at(4).set(x,   y+h);
        _tc.at(5).set(x,   y);
    }
    else {
        _tc.at(0).set(x,   y);
        _tc.at(1).set(x+w, y);
        _tc.at(2).set(x+w, y+h);
        _tc.at(4).set(x,   y+h);
    }
    
    loadTexCoords<2>(&_tc.at(0).x);
}

void loadTexCoords(float w, float h)
{
    loadTexCoords(0.f, 0.f, w, h);
}

void loadTexCoords(const Rectangle& r)
{
    loadTexCoords(r.x, r.y, r.w, r.h);
}

void drawRect(float w, float h)
{
    drawRect(0.f, 0.f, w, h);
}

static std::vector<Vec2f> _vt(6);

void drawRect(float x, float y, float w, float h)
{
    if (getAlign()) {
        x = aligned(x);
        y = aligned(y);
        w = aligned(w);
        h = aligned(h);
    }
    
    if (getFill()) {
        if (_drawRectMode == DRAW_RECT_CENTER) {
            _vt.at(0).set(x - 0.5f * w, y - 0.5f * h);
            _vt.at(1).set(x + 0.5f * w, y - 0.5f * h);
            _vt.at(2).set(x + 0.5f * w, y + 0.5f * h);
            
            _vt.at(3).set(x + 0.5f * w, y + 0.5f * h);
            _vt.at(4).set(x - 0.5f * w, y + 0.5f * h);
            _vt.at(5).set(x - 0.5f * w, y - 0.5f * h);
            
        }
        else {
            _vt.at(0).set(x,     y);
            _vt.at(1).set(x + w, y);
            _vt.at(2).set(x + w, y + h);
            
            _vt.at(3).set(x + w, y + h);
            _vt.at(4).set(x,     y + h);
            _vt.at(5).set(x,     y);
        }
        
        loadVertices<2>(&_vt.at(0).x);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    else {
        if (_drawRectMode == DRAW_RECT_CENTER) {
            _vt.at(0).set(x - 0.5f * w, y - 0.5f * h);
            _vt.at(1).set(x + 0.5f * w, y - 0.5f * h);
            _vt.at(2).set(x + 0.5f * w, y + 0.5f * h);
            _vt.at(3).set(x - 0.5f * w, y + 0.5f * h);
        }
        else {
            _vt.at(0).set(x,     y);
            _vt.at(1).set(x + w, y);
            _vt.at(2).set(x + w, y + h);
            _vt.at(3).set(x,     y + h);
        }
        
        loadVertices<2>(&_vt.at(0).x);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
    }
}

#pragma mark ___________________________________________________________________
void drawTexture(const Texture& tex)
{
    drawTexture(tex, 0.f, 0.f, tex.getWidth(), tex.getHeight());
}

void drawTexture(const Texture& tex, float x, float y)
{
    drawTexture(tex, x, y, tex.getWidth(), tex.getHeight());
}

void drawTexture(const Texture& tex, float x, float y, float scale)
{
    drawTexture(tex, x, y, tex.getWidth() * scale, tex.getHeight() * scale);
}

void drawTexture(const Texture& tex, float x, float y, float w, float h)
{
    tex.bind();
    if (getTextureTarget() == GL_TEXTURE_2D) {
        loadNormalizedTexCoords();
    }
    else {
        loadTexCoords(0.f, 0.f, tex.getWidth(), tex.getHeight());
    }
    drawRect(x, y, w, h);
    tex.unbind();
}

#pragma mark ___________________________________________________________________
void setDrawVerticesMode(GLenum mode)
{
    _drawVerticesMode = mode;
}

GLenum getDrawVerticesMode()
{
    return _drawVerticesMode;
}

void setDrawCircleResolution(int res)
{
    _drawCircleResolution = MAX(res, 0);
}

void setRectMode(DrawRectMode mode)
{
    _drawRectMode =  mode;
}

DrawRectMode getRectMode()
{
    return _drawRectMode;
}

void setTextureTarget(GLenum target)
{
    _textureTarget = target;
}

GLenum getTextureTarget()
{
    return _textureTarget;
}

#pragma mark ___________________________________________________________________
void loadColors(const float* colors)
{
    if (_useAttribArray) {
        glVertexAttribPointer(fl::ATTRIB_COLOR,
                              4,
                              GL_FLOAT,
                              GL_FALSE,
                              sizeof(float) * 4,
                              colors);
    }
    else {
        glColorPointer(4, GL_FLOAT, sizeof(float) * 4, colors);
    }
}

void loadColors(const std::vector<fl::Vec4f>& colors)
{
    loadColors(&colors.at(0).x);
}

void loadColors(const std::vector<fl::FloatColor>& colors)
{
    loadColors(&colors.at(0).r);
}

#pragma mark ___________________________________________________________________
#ifndef TARGET_OPENGLES
void translate(Vec3f p)
{
    translate(p.x, p.y, p.z);
}

void translate(float x, float y, float z)
{
    if (getAlign()) {
        x = floorf(x);
        y = floorf(y);
        z = floorf(z);
    }
    glTranslatef(x, y, z);
}

void scale(float s)
{
    scale(s, s, s);
}

void scale(float sx, float sy, float sz)
{
    glScalef(sx, sy, sz);
}

#endif

FL_NAMESPACE_END