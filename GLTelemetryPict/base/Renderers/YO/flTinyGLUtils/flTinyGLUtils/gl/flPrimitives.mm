//
//  flPrimitives.cpp
//  flTinyGLUtils
//
//  Created by Onishi Yoshito on 10/29/13.
//  Copyright (c) 2013 Onishi Yoshito. All rights reserved.
//

#include "flPrimitives.h"
#include "flCommon.h"
#include "flUtils.h"
#include "flVec3f.h"
#include "flVec2f.h"
#include <vector>

using namespace fl;
using namespace std;

RectPrimitive::RectPrimitive()
{
    
}

RectPrimitive::~RectPrimitive()
{
    mVbo.destoroy();
}

void RectPrimitive::setup(float w,
                          float h,
                          bool fromCenter,
                          bool makeTexcoords,
                          bool makeNormals)
{
    width = w;
    height = h;
    
    mVbo.destoroy();
    
    GLfloat texCoords[] =
    {
        0.f, 0.f,
        1.f, 0.f,
        1.f, 1.f,
        
        1.f, 1.f,
        0.f, 1.f,
        0.f, 0.f,
    };
    
    GLfloat normals[] =
    {
        0.f, 0.f, 1.f,
        0.f, 0.f, 1.f,
        0.f, 0.f, 1.f,
        
        0.f, 0.f, 1.f,
        0.f, 0.f, 1.f,
        0.f, 0.f, 1.f,
    };
    
    if (fromCenter) {
        GLfloat vertices[] =
        {
            -0.5f * w, -0.5f * h, 0.0f,
            0.5f * w, -0.5f * h, 0.0f,
            0.5f * w,  0.5f * h, 0.0f,
            
            0.5f * w,  0.5f * h, 0.0f,
            -0.5f * w,  0.5f * h, 0.0f,
            -0.5f * w, -0.5f * h, 0.0f,
        };
        
        mVbo.setData(fl::ATTRIB_VERTEX, vertices, 3, GL_FLOAT, NUM_VERTICES, GL_STATIC_DRAW);
        
        if (makeNormals) {
            mVbo.setData(fl::ATTRIB_NORMAL, normals, 3, GL_FLOAT, NUM_VERTICES, GL_STATIC_DRAW);
        }
        if (makeTexcoords) {
            mVbo.setData(fl::ATTRIB_TEXCOORD, texCoords, 2, GL_FLOAT, NUM_VERTICES, GL_STATIC_DRAW);
        }
        
        mVbo.setupVao();
    }
    else {
        GLfloat vertices[] =
        {
            0.f, 0.f, 0.0f,
            w,   0.f, 0.0f,
            w,   h,   0.0f,
            
            w,   h,   0.0f,
            0.f, h,   0.0f,
            0.f, 0.f, 0.0f,
        };
        
        mVbo.setData(fl::ATTRIB_VERTEX, vertices, 3, GL_FLOAT, NUM_VERTICES, GL_STATIC_DRAW);
        
        if (makeNormals) {
            mVbo.setData(fl::ATTRIB_NORMAL, normals, 3, GL_FLOAT, NUM_VERTICES, GL_STATIC_DRAW);
        }
        if (makeTexcoords) {
            mVbo.setData(fl::ATTRIB_TEXCOORD, texCoords, 2, GL_FLOAT, NUM_VERTICES, GL_STATIC_DRAW);
        }
        
        mVbo.setupVao();
    }
}

void RectPrimitive::update(float w, float h,  bool fromCenter)
{
    if (fromCenter) {
        GLfloat vertices[] =
        {
            -0.5f * w, -0.5f * h, 0.0f,
            0.5f * w, -0.5f * h, 0.0f,
            0.5f * w,  0.5f * h, 0.0f,
            
            0.5f * w,  0.5f * h, 0.0f,
            -0.5f * w,  0.5f * h, 0.0f,
            -0.5f * w, -0.5f * h, 0.0f,
        };
        
        mVbo.updateData(fl::ATTRIB_VERTEX, vertices, 0, NUM_VERTICES);
    }
    else {
        GLfloat vertices[] =
        {
            0.f, 0.f, 0.0f,
            w,   0.f, 0.0f,
            w,   h,   0.0f,
            
            w,   h,   0.0f,
            0.f, h,   0.0f,
            0.f, 0.f, 0.0f,
        };
        
        mVbo.updateData(fl::ATTRIB_VERTEX, vertices, 0, NUM_VERTICES);
    }
    
}

void RectPrimitive::updateTexCoord(float x0, float y0, float x1, float y1)
{
    GLfloat texCoords[] =
    {
        x0, y0,
        x1, y0,
        x1, y1,
        
        x1, y1,
        x0, y1,
        x0, y0,
    };
    
    mVbo.updateData(fl::ATTRIB_TEXCOORD, texCoords, 0, NUM_VERTICES);
}

void RectPrimitive::draw(int drawMode)
{
    mVbo.draw(drawMode, 0, NUM_VERTICES);
}

#pragma mark ___________________________________________________________________

CirclePrimitive::CirclePrimitive()
{
    
}

CirclePrimitive::~CirclePrimitive()
{
    mVbo.destoroy();
}

void CirclePrimitive::setup(float radius,
                            int resolution,
                            bool makeTexcoords,
                            bool makeNormals)
{
    vector<Vec3f> vertices;
    vertices.clear();
    const float step = M_PI * 2 / (float)resolution;
    for (int i=0; i<resolution; i++) {
        const float x0 = ::cos(step * (float)i) * radius;
        const float y0 = ::sin(step * (float)i) * radius;
        const float x1 = ::cos(step * (float)(i+1)) * radius;
        const float y1 = ::sin(step * (float)(i+1)) * radius;
        vertices.push_back(Vec3f(x0, y0, 0.f));
        vertices.push_back(Vec3f(x1, y1, 0.f));
        vertices.push_back(Vec3f(0.f, 0.f, 0.f));
    }
    
    mVbo.setData(fl::ATTRIB_VERTEX, &vertices.at(0).x, 3, GL_FLOAT, (int)vertices.size(), GL_STATIC_DRAW);
    
    mNumVertices = (int)vertices.size();
}

void CirclePrimitive::draw(int drawMode)
{
    mVbo.draw(drawMode, 0, mNumVertices);
}


SpherePrimitive::SpherePrimitive()
{
    
}

SpherePrimitive::~SpherePrimitive()
{
    mVbo.destoroy();
}

void SpherePrimitive::setup(float radius,
                            int resolution,
                            bool makeTexcoords,
                            bool makeNormals)
{
    float doubleRes = resolution * 2.f;
    float polarInc = PI/(resolution);
    float azimInc = TWO_PI/(doubleRes);
    
    fl::Vec3f vert;
    fl::Vec2f tcoord;
    vector<fl::Vec3f> vertices;
    vector<fl::Vec2f> texCoords;
    vector<fl::Vec3f> normals;
    vector<fl::IndexType> indices;
    vertices.clear();
    texCoords.clear();
    normals.clear();
    indices.clear();
    
    for(float i = 0; i < resolution + 1; i++) {
        float tr = sin(PI-i * polarInc);
        float ny = cos(PI-i * polarInc);
        
        tcoord.y = 1.f - i / resolution;
        
        for(float j = 0; j <= doubleRes; j++) {
            
            float nx = tr * sin(j * azimInc);
            float nz = tr * cos(j * azimInc);
            
            tcoord.x = 1.f - j / (doubleRes);
            
            vert.set(nx, ny, nz);
            if (makeNormals) normals.push_back(vert);
            vert *= radius;
            vertices.push_back(vert);
            if (makeTexcoords) texCoords.push_back(tcoord);
        }
    }
    
    int nr = doubleRes + 1;
    int index1, index2, index3;
    
    for(float iy = 0; iy < resolution; iy++) {
        for(float ix = 0; ix < doubleRes; ix++) {
            
            // first tri //
            if(iy > 0) {
                index1 = (iy+0) * (nr) + (ix+0);
                index2 = (iy+0) * (nr) + (ix+1);
                index3 = (iy+1) * (nr) + (ix+0);
                
                indices.push_back(index1);
                indices.push_back(index2);
                indices.push_back(index3);
            }
            
            if(iy < resolution-1 ) {
                // second tri //
                index1 = (iy+0) * (nr) + (ix+1);
                index2 = (iy+1) * (nr) + (ix+1);
                index3 = (iy+1) * (nr) + (ix+0);
                
                indices.push_back(index1);
                indices.push_back(index2);
                indices.push_back(index3);
                
            }
        }
    }
    
    mVbo.setData(fl::ATTRIB_VERTEX,
                 &vertices.at(0).x,
                 3,
                 GL_FLOAT,
                 (int)vertices.size(),
                 GL_STATIC_DRAW);
    if (makeNormals) {
        mVbo.setData(fl::ATTRIB_NORMAL,
                     &normals.at(0).x,
                     2,
                     GL_FLOAT,
                     (int)normals.size(),
                     GL_STATIC_DRAW);
    }
    if (makeTexcoords) {
        mVbo.setData(fl::ATTRIB_TEXCOORD,
                     &texCoords.at(0).x,
                     2,
                     GL_FLOAT,
                     (int)texCoords.size(),
                     GL_STATIC_DRAW);
    }
    mVbo.setIndexData(&indices.at(0), (int)indices.size(), GL_STATIC_DRAW);
    
    mNumIndices = (int)indices.size();
}

void SpherePrimitive::draw(int drawMode)
{
    mVbo.drawElements(drawMode, mNumIndices);
}