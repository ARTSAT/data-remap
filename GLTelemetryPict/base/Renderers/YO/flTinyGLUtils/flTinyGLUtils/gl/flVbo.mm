//
//  flVbo.cpp
//  flTinyGLUtils
//
//  Created by Onishi Yoshito on 10/29/13.
//  Copyright (c) 2013 Onishi Yoshito. All rights reserved.
//

#include "flVbo.h"
#include "flVec3f.h"
#include "flVec2f.h"
#include "flException.h"
#include "flGraphics.h"

#include <dlfcn.h>
typedef void (* glGenVertexArraysType) (GLsizei n,  GLuint *arrays);
glGenVertexArraysType glGenVertexArraysFunc;
#define glGenVertexArrays								glGenVertexArraysFunc

typedef void (* glDeleteVertexArraysType) (GLsizei n,  GLuint *arrays);
glDeleteVertexArraysType glDeleteVertexArraysFunc;
#define glDeleteVertexArrays							glDeleteVertexArraysFunc

typedef void (* glBindVertexArrayType) (GLuint array);
glBindVertexArrayType glBindVertexArrayFunc;
#define glBindVertexArray								glBindVertexArrayFunc

using namespace fl;
using namespace std;

FL_UNNAMED_NAMESPACE_BEGIN

const GLsizeiptr kVertexStride = sizeof(float) * Vec3f::DIM;
const GLsizeiptr kColorStride = sizeof(float) * 4;
const GLsizeiptr kTexCoordStride = sizeof(float) * Vec2f::DIM;
const GLsizeiptr kNormalStride = sizeof(float) * Vec3f::DIM;
const GLsizeiptr kIndexStride = sizeof(IndexType);

bool _initedVaoFuncs = false;

bool _changeClientState = true;

FL_UNNAMED_NAMESPACE_END

void Vbo::setChangeClientStateAuto(bool change)
{
    _changeClientState = change;
}

Vbo::Vbo() :
mIndexId(0),
mVaoId(0),
mHasIndices(false),
mHasVao(false)
#ifndef TARGET_OPENGLES
,
mVertexId(0),
mColorId(0),
mTexCoordId(0),
mNormalId(0),
mVertexSize(0),
mColorSize(0),
mTexCoordSize(0),
mNormalSize(0)
#endif
{
    mIds.clear();
    mTypes.clear();
    mNumCoords.clear();
    mSizes.clear();
}

Vbo::~Vbo()
{
    destoroy();
}

#ifndef TARGET_OPENGLES
#pragma mark _______________________________________________________________
void Vbo::setVertexData(const std::vector<Vec3f>& vertices, GLenum usage)
{
    if (!mVertexId) {
        glGenBuffers(1, &mVertexId);
    }
    glBindBuffer(GL_ARRAY_BUFFER, mVertexId);
    glBufferData(GL_ARRAY_BUFFER,
                 vertices.size() * kVertexStride,
                 &vertices.at(0).x,
                 usage);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    mVertexSize = (GLsizei)vertices.size();
}

void Vbo::setColorData(const std::vector<FloatColor>& colors, GLenum usage)
{
    if (!mColorId) {
        glGenBuffers(1, &mColorId);
    }
    glBindBuffer(GL_ARRAY_BUFFER, mColorId);
    glBufferData(GL_ARRAY_BUFFER,
                 colors.size() * kColorStride,
                 &colors.at(0).r,
                 usage);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    mColorSize = (GLsizei)colors.size();
}

void Vbo::setTexCoordData(const std::vector<Vec2f>& texCoords, GLenum usage)
{
    if (!mTexCoordId) {
        glGenBuffers(1, &mTexCoordId);
    }
    glBindBuffer(GL_ARRAY_BUFFER, mTexCoordId);
    glBufferData(GL_ARRAY_BUFFER,
                 texCoords.size() * kTexCoordStride,
                 &texCoords.at(0).x,
                 usage);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    mTexCoordSize = (GLsizei)texCoords.size();
}

void Vbo::setNormalData(const std::vector<Vec3f>& normals, GLenum usage)
{
    if (!mNormalId) {
        glGenBuffers(1, &mNormalId);
    }
    glBindBuffer(GL_ARRAY_BUFFER, mNormalId);
    glBufferData(GL_ARRAY_BUFFER,
                 normals.size() * kNormalStride,
                 &normals.at(0).x,
                 usage);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    mNormalSize = (GLsizei)normals.size();
}
#endif

#pragma mark _______________________________________________________________

void Vbo::setIndexData(const std::vector<IndexType>& indices, GLenum usage)
{
    setIndexData(&indices.at(0), indices.size(), usage);
}

void Vbo::setIndexData(const IndexType* indices,
                       GLsizeiptr total,
                       GLenum usage)
{
    if (mIndexId==0) {
        glGenBuffers(1, &mIndexId);
    }
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 total * kIndexStride,
                 &indices[0],
                 usage);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    mIndexSize = (GLsizei)total;
    mHasIndices = true;
}

#pragma mark _______________________________________________________________

void Vbo::setupVao()
{
    if (!_initedVaoFuncs) {
#ifndef TARGET_OPENGLES
        glGenVertexArrays = (glGenVertexArraysType)dlsym(RTLD_DEFAULT, "glGenVertexArraysOES");
        glDeleteVertexArrays =  (glDeleteVertexArraysType)dlsym(RTLD_DEFAULT, "glDeleteVertexArraysOES");
        glBindVertexArray =  (glBindVertexArrayType)dlsym(RTLD_DEFAULT, "glBindVertexArrayArraysOES");
#else
        glGenVertexArrays = (glGenVertexArraysType)dlsym(RTLD_DEFAULT, "glGenVertexArrays");
        glDeleteVertexArrays =  (glDeleteVertexArraysType)dlsym(RTLD_DEFAULT, "glDeleteVertexArrays");
        glBindVertexArray =  (glBindVertexArrayType)dlsym(RTLD_DEFAULT, "glBindVertexArrayArrays");
#endif
        const bool supportVao = glGenVertexArrays && glDeleteVertexArrays && glBindVertexArray;
        assert(supportVao && "VAO is not supported!");
        if (!supportVao) {
            flThrowException("VAO is not supported!");
        }
    }
    
    if (mVaoId == 0) {
        glGenVertexArrays(1, &mVaoId);
    }
    glBindVertexArray(mVaoId);
    
    bind();
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glPopClientAttrib();
    mHasVao = true;
}

#ifndef TARGET_OPENGLES
#pragma mark _______________________________________________________________
void Vbo::updateVertexData(const std::vector<Vec3f>& vertices,
                           GLintptr offset,
                           GLsizeiptr total)
{
    if (total <= 0) {
        total = vertices.size();
    }
    if (!mVertexId) {
        flThrowException("Buffer haven't created yet!");
    }
    if (offset + total > mVertexSize) {
        flThrowException("Buffer out of range!");
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, mVertexId);
    glBufferSubData(GL_ARRAY_BUFFER,
                    offset * kVertexStride,
                    total * kVertexStride,
                    &vertices.at(0).x);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Vbo::updateColorData(const std::vector<FloatColor>& colors,
                          GLintptr offset,
                          GLsizeiptr total)
{
    if (total <= 0) {
        total = colors.size();
    }
    if (!mColorId) {
        flThrowException("Buffer haven't created yet!");
    }
    if (offset + total > mColorSize) {
        flThrowException("Buffer out of range!");
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, mColorId);
    glBufferSubData(GL_ARRAY_BUFFER,
                    offset * kColorStride,
                    total * kColorStride,
                    &colors.at(0).r);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Vbo::updateTexCoordData(const std::vector<Vec2f>& texCoords,
                             GLintptr offset,
                             GLsizeiptr total)
{
    if (total <= 0) {
        total = texCoords.size();
    }
    if (!mTexCoordId) {
        flThrowException("Buffer haven't created yet!");
    }
    if (offset + total > mTexCoordSize) {
        flThrowException("Buffer out of range!");
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, mTexCoordId);
    glBufferSubData(GL_ARRAY_BUFFER,
                    offset * kTexCoordStride,
                    total * kTexCoordStride,
                    &texCoords.at(0).x);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Vbo::updateNormalData(const std::vector<Vec3f>& normals,
                           GLintptr offset,
                           GLsizeiptr total)
{
    if (total <= 0) {
        total = normals.size();
    }
    if (!mNormalId) {
        flThrowException("Buffer haven't created yet!");
    }
    if (offset + total > mNormalSize) {
        flThrowException("Buffer out of range!");
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, mNormalId);
    glBufferSubData(GL_ARRAY_BUFFER,
                    offset * kNormalStride,
                    total * kNormalStride,
                    &normals.at(0).x);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
#endif

#pragma mark _______________________________________________________________
void Vbo::updateIndexData(const IndexType* indices,
                          GLintptr offset,
                          GLsizeiptr total)
{
    if (!mIndexId) {
        flThrowException("Indices haven't created yet!");
    }
    glBindBuffer(GL_ARRAY_BUFFER, mIndexId);
    glBufferSubData(GL_ARRAY_BUFFER,
                    offset,
                    total*sizeof(IndexType),
                    &indices[0]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

#pragma mark _______________________________________________________________
GLuint Vbo::getId(GLuint location)
{
    if (mIds.find(location) != mIds.end()) {
        return mIds[location];
    }
    return 0;
}

GLsizei Vbo::getSize(GLuint location)
{
    if (mSizes.find(location) != mSizes.end()) {
        return mSizes[location];
    }
    return 0;
}

#pragma mark _______________________________________________________________
void Vbo::bind()
{
    
    if (mHasVao) {
        glBindVertexArray(mVaoId);
    }
    else {
#ifndef TARGET_OPENGLES
        if (_changeClientState) {
            glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);
            if (mVertexId) {
                glEnableClientState(GL_VERTEX_ARRAY);
            }
            if (mColorId) {
                glEnableClientState(GL_COLOR_ARRAY);
            }
            if (mTexCoordId) {
                glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            }
            if (mNormalId) {
                glEnableClientState(GL_NORMAL_ARRAY);
            }
        }
        if (mVertexId) {
            glBindBuffer(GL_ARRAY_BUFFER, mVertexId);
            glVertexPointer(3, GL_FLOAT, 0, NULL);
        }
        if (mColorId) {
            glBindBuffer(GL_ARRAY_BUFFER, mColorId);
            glColorPointer(4, GL_FLOAT, 0, NULL);
        }
        if (mTexCoordId) {
            glBindBuffer(GL_ARRAY_BUFFER, mTexCoordId);
            glTexCoordPointer(2, GL_FLOAT, 0, NULL);
        }
        if (mNormalId) {
            glBindBuffer(GL_ARRAY_BUFFER, mNormalId);
            glNormalPointer(GL_FLOAT, 0, NULL);
        }
        
#endif
        for (LocationMap::iterator it=mIds.begin(); it!=mIds.end(); ++it) {
            glBindBuffer(GL_ARRAY_BUFFER, mIds[it->first]);
            glEnableVertexAttribArray(it->first);
            glVertexAttribPointer(it->first,
                                  mNumCoords[it->first],
                                  mTypes[it->first],
                                  GL_FALSE,
                                  0,
                                  0);
        }
        if (mHasIndices) {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexId);
        }
    }
}

void Vbo::unbind()
{
    if (mHasVao) {
        glBindVertexArray(0);
    }
    else {
#ifndef TARGET_OPENGLES
        if (_changeClientState) {
            glDisableClientState(GL_VERTEX_ARRAY);
            if (mColorId) glDisableClientState(GL_COLOR_ARRAY);
            if (mTexCoordId) glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            if (mNormalId) glDisableClientState(GL_NORMAL_ARRAY);
            
            glPopClientAttrib();
        }
#endif
        if (mHasIndices) {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

#pragma mark _______________________________________________________________
void Vbo::draw(GLenum drawMode)
{
    bind();
#ifdef TARGET_OPENGLES
    if (mIds.find(ATTRIB_VERTEX) != mIds.end()) {
        glDrawArrays(drawMode, 0, mSizes[ATTRIB_VERTEX]);
    }
    else {
        flThrowException("Buffer haven't allocated yet!");
    }
#else
    if (mVertexId) {
        glDrawArrays(drawMode, 0, mVertexSize);
    }
    else if (mIds.find(ATTRIB_VERTEX) != mIds.end()) {
        glDrawArrays(drawMode, 0, mSizes[ATTRIB_VERTEX]);
    }
    else {
        flThrowException("Buffer haven't allocated yet!");
    }
#endif
    unbind();
}

void Vbo::drawElements(GLenum drawMode)
{
    if (!mIndexId) {
        flThrowException("Indices haven't allocated yet!");
    }
    bind();
#ifdef TARGET_OPENGLES
    glDrawElements(drawMode, mIndexSize, GL_UNSIGNED_SHORT, NULL);
#else
    glDrawElements(drawMode, mIndexSize, GL_UNSIGNED_INT, NULL);
#endif
    unbind();
}

void Vbo::draw(GLenum drawMode, GLint first, GLsizei total)
{
#ifdef TARGET_OPENGLES
    if (mIds.find(ATTRIB_VERTEX) != mIds.end()) {
        flThrowException("Buffer haven't allocated yet!");
    }
#else
    if (!mVertexId || mIds.find(ATTRIB_VERTEX) != mIds.end()) {
        flThrowException("Buffer haven't allocated yet!");
    }
#endif
    
    bind();
    glDrawArrays(drawMode, first, total);
    unbind();
}

void Vbo::drawElements(GLenum drawMode, GLsizei amt)
{
    if (!mIndexId) {
        flThrowException("Indices haven't allocated yet!");
    }
    bind();
#ifdef TARGET_OPENGLES
    glDrawElements(drawMode, amt, GL_UNSIGNED_SHORT, NULL);
#else
    glDrawElements(drawMode, amt, GL_UNSIGNED_INT, NULL);
#endif
    unbind();
}

#pragma mark _______________________________________________________________
void Vbo::destoroy()
{
    for (LocationMap::iterator it=mIds.begin(); it!=mIds.end(); ++it) {
        glDeleteBuffers(1, &it->second);
        it->second = 0;
    }
    mIds.clear();
    mNumCoords.clear();
    mTypes.clear();
    mSizes.clear();
    
#ifndef TARGET_OPENGLES
    if (mVertexId) {
        glDeleteBuffers(1, &mVertexId);
        mVertexId = 0;
        mVertexSize = 0;
    }
    if (mColorId) {
        glDeleteBuffers(1, &mColorId);
        mColorId = 0;
        mColorSize = 0;
    }
    if (mTexCoordId) {
        glDeleteBuffers(1, &mTexCoordId);
        mTexCoordId = 0;
        mTexCoordSize = 0;
    }
    if (mNormalId) {
        glDeleteBuffers(1, &mNormalId);
        mNormalId = 0;
        mNormalSize = 0;
    }
#endif
    if (mIndexId != 0) {
        glDeleteBuffers(1, &mIndexId);
        mIndexId = 0;
        mIndexSize = 0;
    }
    
    if (mVaoId != 0) {
        glDeleteVertexArrays(1, &mVaoId);
        mVaoId = 0;
    }
    
    mHasIndices = false;
    mHasVao = false;
    mIndexId = 0;
    mVaoId = 0;
}

void Vbo::generate(int begin,
                   int total,
                   std::function<Vec3f(int i)> generator,
                   GLenum usage)
{
    vector<Vec3f> v;
    for (int i{begin}; i<total; i++) {
        v.push_back(generator(i));
    }
    if (v.empty()) {
        cout << "Notice: Create empty VBO." << endl;
        return;
    }
    if (getAlign()) align(v);
    setVertexData(v, usage);
}

void Vbo::generate(int begin,
                   int total,
                   function<vector<Vec3f>(int i)> generator,
                   GLenum usage)
{
    vector<Vec3f> v;
    generate(v, begin, total, generator, usage);
};

void Vbo::generate(vector<Vec3f>& v,
                   int begin,
                   int total,
                   function<vector<Vec3f>(int i)> generator,
                   GLenum usage)
{
    for (int i{begin}; i<total; i++) {
        auto n = generator(i);
        v.insert(v.end(), n.begin(), n.end());
    }
    if (v.empty()) {
        cout << "Notice: Create empty VBO." << endl;
        return;
    }
    if (getAlign()) align(v);
    setVertexData(v, usage);
}

void Vbo::generate(int begin,
                   int total,
                   function<vector<Vec3f>(int i)> generatorV,
                   function<vector<FloatColor>(int i)> generatorC,
                   GLenum usage)
{
    vector<Vec3f> v;
    vector<FloatColor> c;
    
    for (int i{begin}; i<total; i++) {
        auto nv = generatorV(i);
        v.insert(v.end(), nv.begin(), nv.end());
        auto nc = generatorC(i);
        c.insert(c.end(), nc.begin(), nc.end());
    }
    if (v.empty()) {
        cout << "Notice: Create empty VBO." << endl;
        return;
    }
    if (getAlign()) align(v);
    setVertexData(v, usage);
    setColorData(c, usage);
};

void Vbo::generate(int beginX,
                   int beginY,
                   int totalX,
                   int totalY,
                   function<vector<Vec3f>(int i, int j)> generator,
                   GLenum usage)
{
    vector<Vec3f> v;
    
    for (int i{beginX}; i<totalX; i++) {
        for (int j{beginY}; j<totalY; j++) {
            auto n = generator(i, j);
            v.insert(v.end(), n.begin(), n.end());
        }
    }
    if (v.empty()) {
        cout << "Notice: Create empty VBO." << endl;
        return;
    }
    if (getAlign()) align(v);
    setVertexData(v, usage);
};

