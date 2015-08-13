//
//  flVbo.h
//  flTinyGLUtils
//
//  Created by Onishi Yoshito on 10/29/13.
//  Copyright (c) 2013 Onishi Yoshito. All rights reserved.
//

#ifndef __flTinyGLUtils__flVbo__
#define __flTinyGLUtils__flVbo__

#include <map>
#include <vector>
#include <functional>

#include "flCommon.h"
#include "flColor.h"

FL_NAMESPACE_BEGIN

class Vec2f;
class Vec3f;

#ifdef TARGET_OPENGLES
typedef unsigned short IndexType;
#else
typedef unsigned int IndexType;
#endif

class Vbo {
    typedef std::map<int, GLuint> LocationMap;
public:
#ifndef TARGET_OPENGLES
    static void setChangeClientStateAuto(bool change); // for optimization
#endif
    
    Vbo();
    virtual ~Vbo();
    
    template<typename Type>
    void setData(GLuint location,
                 const Type* attrib0x,
                 int numCoords,
                 GLenum type,
                 GLsizeiptr total,
                 GLenum usage);
    
#ifndef TARGET_OPENGLES
    void setVertexData(const std::vector<Vec3f>& vertices, GLenum usage = GL_STATIC_DRAW);
    void setColorData(const std::vector<FloatColor>& colors, GLenum usage = GL_STATIC_DRAW);
    void setTexCoordData(const std::vector<Vec2f>& texCoords, GLenum usage = GL_STATIC_DRAW);
    void setNormalData(const std::vector<Vec3f>& normals, GLenum usage = GL_STATIC_DRAW);
#endif
    
    void setIndexData(const std::vector<IndexType>& indices, GLenum usage);
    void setIndexData(const IndexType* indices, GLsizeiptr total, GLenum usage);
    
    void setupVao();
    
    template<typename Type>
    void updateData(GLuint location,
                    const Type* attrib0x,
                    GLintptr offset,
                    GLsizeiptr total);
    
#ifndef TARGET_OPENGLES
    void updateVertexData(const std::vector<Vec3f>& vertices,
                          GLintptr offset = 0,
                          GLsizeiptr total = 0);
    void updateColorData(const std::vector<FloatColor>& colors,
                         GLintptr offset = 0,
                         GLsizeiptr total = 0);
    void updateTexCoordData(const std::vector<Vec2f>& texCoords,
                            GLintptr offset = 0,
                            GLsizeiptr total = 0);
    void updateNormalData(const std::vector<Vec3f>& normals,
                          GLintptr offset = 0,
                          GLsizeiptr total = 0);
#endif
    
    void updateIndexData(const std::vector<IndexType>& indices,
                         GLintptr offset = 0,
                         GLsizeiptr total = 0);
    
    void updateIndexData(const IndexType* indices,
                         GLintptr offset,
                         GLsizeiptr total);
    
    GLuint getId(GLuint location);
    GLsizei getSize(GLuint location);
    
#ifndef TARGET_OPENGLES
    GLuint getVertexId() const {return mVertexId; }
    GLuint getColorId() const {return mColorId; }
    GLuint getTexCoordId() const {return mTexCoordId; }
    GLuint getNormalId() const {return mNormalId; }
    
    GLsizei getVertexSize() const { return mVertexSize; }
    GLsizei getColorSize() const { return mColorSize; }
    GLsizei getTexCoordSize() const { return mTexCoordSize; }
    GLsizei getNormalSize() const { return mNormalSize; }
#endif
    
    void draw(GLenum drawMode);
    void drawElements(GLenum drawMode);
    
    void draw(GLenum drawMode, GLint first, GLsizei total);
    void drawElements(GLenum drawMode, GLsizei amt);
    
    void destoroy();
    
    void bind();
    void unbind();
    
    // cool mesh generator with rambda and move semantics
    void generate(int begin,
                  int total,
                  std::function<Vec3f(int i)> generator,
                  GLenum usage = GL_STATIC_DRAW);
    
    void generate(int begin,
                  int total,
                  std::function<std::vector<Vec3f>(int i)> generator,
                  GLenum usage = GL_STATIC_DRAW);
    
    void generate(std::vector<Vec3f>& v,
                  int begin,
                  int total,
                  std::function<std::vector<Vec3f>(int i)> generator,
                  GLenum usage = GL_STATIC_DRAW);
    
    void generate(int begin,
                  int total,
                  std::function<std::vector<Vec3f>(int i)> generatorV,
                  std::function<std::vector<FloatColor>(int i)> generatorC,
                  GLenum usage = GL_STATIC_DRAW);
    
    void generate(int beginX,
                  int beginY,
                  int totalX,
                  int totalY,
                  std::function<std::vector<Vec3f>(int i, int j)> generator,
                  GLenum usage = GL_STATIC_DRAW);
    
private:
    Vbo(const Vbo&) = delete;
    Vbo& operator=(const Vbo&) = delete;
    
    bool                        mHasIndices;
    bool                        mHasVao;
    
    GLuint                      mIndexId;
    GLsizei                     mIndexSize;
    
    GLuint                      mVaoId;
    
    LocationMap                 mIds;
    std::map<int, GLenum>       mTypes;
    std::map<int, int>          mNumCoords;
    std::map<int, GLsizei>      mSizes;
    
#ifndef TARGET_OPENGLES
    GLuint                      mVertexId;
    GLuint                      mColorId;
    GLuint                      mTexCoordId;
    GLuint                      mNormalId;
    
    GLsizei                     mVertexSize;
    GLsizei                     mColorSize;
    GLsizei                     mTexCoordSize;
    GLsizei                     mNormalSize;
#endif
};

#pragma mark _______________________________________________________________
template<typename Type>
void Vbo::setData(GLuint location,
                  const Type* attrib0x,
                  int numCoords,
                  GLenum type,
                  GLsizeiptr total,
                  GLenum usage)
{
    if (mIds.find(location)==mIds.end()) {
        glGenBuffers(1, &(mIds[location]));
    }
    
    mNumCoords[location] = numCoords;
    mSizes[location] = (GLsizei)total;
    mTypes[location] = type;
    
    glBindBuffer(GL_ARRAY_BUFFER, mIds[location]);
    glBufferData(GL_ARRAY_BUFFER,
                 total * numCoords * sizeof(Type),
                 attrib0x,
                 usage);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

template<typename Type>
void Vbo::updateData(GLuint location,
                     const Type* attrib0x,
                     GLintptr offset,
                     GLsizeiptr total)
{
    if (mIds.find(location)!=mIds.end() && mIds[location]!=0 && total<=mSizes[location]) {
        glBindBuffer(GL_ARRAY_BUFFER, mIds[location]);
        glBufferSubData(GL_ARRAY_BUFFER,
                        offset,
                        total * mNumCoords[location] * sizeof(Type),
                        attrib0x);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

FL_NAMESPACE_END

#endif /* defined(__flTinyGLUtils__flVbo__) */
