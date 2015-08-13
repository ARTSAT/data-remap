//
//  flFbo.h
//  flTinyGLUtils
//
//  Created by Onishi Yoshito on 10/29/13.
//  Copyright (c) 2013 Onishi Yoshito. All rights reserved.
//

#ifndef __flTinyGLUtils__flFbo__
#define __flTinyGLUtils__flFbo__

#include "flCommon.h"
#include "flTexture.h"

FL_NAMESPACE_BEGIN

class Fbo {
public:
    Fbo();
    ~Fbo();
    
    void create(GLsizei w,
                GLsizei h,
                GLenum internalFormat = GL_RGBA,
                GLenum format = GL_RGBA,
                GLenum type = GL_UNSIGNED_BYTE,
                bool hasDepthStencil = false);
    void destoroy();
    
    void bindFramebuffer() const;
    void unbindFramebuffer() const;
    void bindTexture() const;
    void unbindTexture() const;
    
    inline
    int getWidth() const { return mWidth; }
    inline
    int getHeight() const { return mHeight; }
    
    Texture& getTexture() { return mTexture; }
    const Texture& getTexture() const { return mTexture; }
    
private:
    Fbo(const Fbo& rhs);
    Fbo& operator=(const Fbo& rhs);
    
    void checkFboStatus() const;
    
    Texture mTexture;
    
    GLuint mFboId;
    GLuint mRboId;
    
    int mWidth;
    int mHeight;
    
    mutable GLint mDefaultFbo;
    mutable GLint mSavedViewport[4];
};

FL_NAMESPACE_END

#endif /* defined(__flTinyGLUtils__flFbo__) */
