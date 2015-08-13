//
//  flPrimitives.h
//  flTinyGLUtils
//
//  Created by Onishi Yoshito on 10/29/13.
//  Copyright (c) 2013 Onishi Yoshito. All rights reserved.
//

#ifndef __DrawXmasTest__flPrimitives__
#define __DrawXmasTest__flPrimitives__

#include "flVbo.h"
#include "flVec4f.h"
#include "flCommon.h"

FL_NAMESPACE_BEGIN

#pragma mark ___________________________________________________________________

class BasePrimitive {
public:
    virtual ~BasePrimitive() {}
    virtual void draw(int drawMode = GL_TRIANGLES) = 0;
    
    void destoroy() { mVbo.destoroy(); }
    
    inline
    fl::Vbo& getVbo() { return mVbo; }
    
    inline
    const fl::Vbo& getVbo() const { return mVbo; }
    
protected:
    fl::Vbo mVbo;
};

#pragma mark ___________________________________________________________________

class RectPrimitive : public BasePrimitive {
public:
    RectPrimitive();
    virtual ~RectPrimitive();
    
    void setup(float w,
               float h,
               bool fromCenter = true,
               bool makeTexcoords = false,
               bool makeNormals = false);
    void update(float w, float h, bool fromCenter = true);
    void updateTexCoord(float x0, float y0, float x1, float y1);
    virtual void draw(int drawMode = GL_TRIANGLES);
    
    static const int NUM_VERTICES = 6;
    
    float width, height;
};

#pragma mark ___________________________________________________________________

class CirclePrimitive : public BasePrimitive {
public:
    CirclePrimitive();
    virtual ~CirclePrimitive();
    
    void setup(float radius,
               int resolution,
               bool makeTexcoords = false,
               bool makeNormals = false);
    virtual void draw(int drawMode = GL_TRIANGLES);
private:
    int mNumVertices;
};

#pragma mark ___________________________________________________________________

class SpherePrimitive : public BasePrimitive {
public:
    SpherePrimitive();
    virtual ~SpherePrimitive();
    
    void setup(float radius,
               int resolution,
               bool makeTexcoords = false,
               bool makeNormals = false);
    virtual void draw(int drawMode = GL_TRIANGLES);
private:
    int mNumIndices;
};


FL_NAMESPACE_END

#endif /* defined(__flTinyGLUtils__flPrimitives__) */
