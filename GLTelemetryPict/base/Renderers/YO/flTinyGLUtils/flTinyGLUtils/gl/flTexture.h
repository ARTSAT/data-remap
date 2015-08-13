//
//  flTexture.h
//  flTinyGLUtils
//
//  Created by Onishi Yoshito on 10/29/13.
//  Copyright (c) 2013 Onishi Yoshito. All rights reserved.
//

#ifndef __flTinyGLUtils__flTexture__
#define __flTinyGLUtils__flTexture__

#include <string>
#include "flCommon.h"

FL_NAMESPACE_BEGIN

class Texture {
public:
    Texture();
    ~Texture();
    
    void create();
    void destoroy();
    
    void load(GLenum internalFormat,
              GLsizei width,
              GLsizei height,
              GLenum format,
              GLenum type,
              const GLvoid* data);
    
    void update(GLint x,
                GLint y,
                GLsizei w,
                GLsizei h,
                const GLvoid *pixels);
    
    void generateNoise(GLsizei width, GLsizei height); // debug
    
    void setFilter(GLenum min, GLenum mag);
    void setWrap(GLenum S, GLenum T);
    
    void bind() const;
    void unbind() const;
    
    int getWidth() const { return mWidth; }
    int getHeight() const { return mHeight; }
    
    GLuint getId() const { return mId; }
    GLenum getTarget() const { return mTarget; }
    
private:
    Texture(const Texture& rhs);
    Texture& operator=(const Texture& rhs);
    
    GLuint mId;
    GLenum mTarget;
    GLenum mInternalFormat;
    GLenum mFormat;
    GLenum mType;
    int mWidth;
    int mHeight;
};

FL_NAMESPACE_END

#endif /* defined(__flTinyGLUtils__flTexture__) */
