//
//  flFbo.cpp
//  flTinyGLUtils
//
//  Created by Onishi Yoshito on 10/29/13.
//  Copyright (c) 2013 Onishi Yoshito. All rights reserved.
//

#include "flFbo.h"
#include "flException.h"
#include "flGraphics.h"
#include <iostream>

using namespace fl;

Fbo::Fbo() :
mFboId(0),
mRboId(0),
mDefaultFbo(0)
{
}

Fbo::~Fbo()
{
    destoroy();
}

#pragma mark ___________________________________________________________________
void Fbo::create(GLsizei w,
                 GLsizei h,
                 GLenum format,
                 GLenum internalFormat,
                 GLenum type,
                 bool hasDepthStencil)
{
    mWidth = w;
    mHeight = h;
    
    destoroy();
    
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &mDefaultFbo);
    
    mTexture.create();
    mTexture.load(internalFormat, w, h, format, type, NULL);
    
    glGenFramebuffers(1, &mFboId);
    glBindFramebuffer(GL_FRAMEBUFFER, mFboId);
    glFramebufferTexture2D(GL_FRAMEBUFFER,
                           GL_COLOR_ATTACHMENT0,
                           mTexture.getTarget(),
                           mTexture.getId(),
                           0);
    
    if (hasDepthStencil) {
        glGenRenderbuffers(1, &mRboId);
        glBindRenderbuffer(GL_RENDERBUFFER, mRboId);
#ifdef TARGET_OPENGLES
        glRenderbufferStorage(GL_DEPTH_COMPONENT,
                              GL_DEPTH_COMPONENT24_OES,
                              w,
                              h);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                                  GL_DEPTH_ATTACHMENT,
                                  GL_RENDERBUFFER,
                                  mRboId);
#else
        glRenderbufferStorage(GL_DEPTH_COMPONENT,
                              GL_DEPTH24_STENCIL8,
                              w,
                              h);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                                  GL_DEPTH_ATTACHMENT,
                                  GL_RENDERBUFFER,
                                  mRboId);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                                  GL_STENCIL_ATTACHMENT,
                                  GL_RENDERBUFFER,
                                  mRboId);
#endif
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }
    
    checkFboStatus();
    
    glClearColor(1.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindFramebuffer(GL_FRAMEBUFFER, mDefaultFbo);
}

void Fbo::destoroy()
{
    if (mFboId) {
        glDeleteFramebuffers(1, &mFboId);
        mFboId = 0;
    }
    if (mRboId) {
        glDeleteRenderbuffers(1, &mRboId);
        mRboId = 0;
    }
    mTexture.destoroy();
}

#pragma mark ___________________________________________________________________
void Fbo::bindFramebuffer() const
{
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &mDefaultFbo);
    
    glGetIntegerv(GL_VIEWPORT, mSavedViewport);
    glBindFramebuffer(GL_FRAMEBUFFER, mFboId);
    glViewport(0, 0, mWidth, mHeight);
    
#ifndef TARGET_OPENGLES
    GLint defaultMatrixMode;
    glGetIntegerv(GL_MATRIX_MODE, &defaultMatrixMode);
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    
    glMatrixMode(defaultMatrixMode);
#endif
}

void Fbo::unbindFramebuffer() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, mDefaultFbo);
    glViewport(mSavedViewport[0], mSavedViewport[1], mSavedViewport[2], mSavedViewport[3]);
    
#ifndef TARGET_OPENGLES
    GLint defaultMatrixMode;
    glGetIntegerv(GL_MATRIX_MODE, &defaultMatrixMode);
    
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    
    glMatrixMode(defaultMatrixMode);
#endif
}

#pragma mark ___________________________________________________________________
void Fbo::bindTexture() const
{
    mTexture.bind();
}

void Fbo::unbindTexture() const
{
    mTexture.unbind();
}

void Fbo::checkFboStatus() const
{
    GLenum status;
    status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    switch(status) {
        case GL_FRAMEBUFFER_COMPLETE:
            std::cout << "FRAMEBUFFER_COMPLETE - OK" << std::endl;
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
            std::cout << "FRAMEBUFFER_INCOMPLETE_ATTACHMENT" << std::endl;
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
            std::cout << "FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT" << std::endl;
            break;
            //case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS:
            //    std::cout << "FRAMEBUFFER_INCOMPLETE_DIMENSIONS" << std::endl;
            //    break;
            //case GL_FRAMEBUFFER_INCOMPLETE_FORMATS:
            //    std::cout << "FRAMEBUFFER_INCOMPLETE_FORMATS" << std::endl;
            //    break;
        case GL_FRAMEBUFFER_UNSUPPORTED:
            std::cout << "FRAMEBUFFER_UNSUPPORTED" << std::endl;
            break;
#ifndef TARGET_OPENGLES
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
            std::cout  << "FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER" << std::endl;
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
            std::cout << "FRAMEBUFFER_INCOMPLETE_READ_BUFFER" << std::endl;
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
            std::cout << "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE" << std::endl;
            break;
#endif
        default:
            std::cout << "UNKNOWN ERROR " << status << std::endl;
            break;
    }
   
}
