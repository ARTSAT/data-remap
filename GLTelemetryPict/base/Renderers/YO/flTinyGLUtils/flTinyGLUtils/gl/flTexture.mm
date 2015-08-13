//
//  flTexture.cpp
//  flTinyGLUtils
//
//  Created by Onishi Yoshito on 10/29/13.
//  Copyright (c) 2013 Onishi Yoshito. All rights reserved.
//

#include "flTexture.h"
#include "flException.h"
#include "flGraphics.h"

using namespace fl;

Texture::Texture() :
mId(0),
mTarget(GL_TEXTURE_2D),
mInternalFormat(GL_RGBA),
mFormat(GL_RGBA),
mType(GL_UNSIGNED_BYTE),
mWidth(0),
mHeight(0)
{
}

Texture::~Texture()
{
    destoroy();
}

#pragma mark ___________________________________________________________________

void Texture::create()
{
    if (mId) {
        glDeleteTextures(1, &mId);
        mId = 0;
    }
    glGenTextures(1, &mId);
    
    mTarget = fl::getTextureTarget();
    
    bind();
    glTexParameterf(mTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(mTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(mTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(mTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    unbind();
}

void Texture::destoroy()
{
    if (mId) {
        glDeleteTextures(1, &mId);
        mId = 0;
    }
}

#pragma mark ___________________________________________________________________

void Texture::load(GLenum internalFormat,
                   GLsizei width,
                   GLsizei height,
                   GLenum format,
                   GLenum type,
                   const GLvoid* data)
{
    if (!mId) {
        flThrowException("Texture haven't created yet");
    }
    
    bind();
    glTexImage2D(mTarget,
                 0,
                 internalFormat,
                 width,
                 height,
                 0,
                 format,
                 type,
                 data);
    unbind();
    
    mInternalFormat = internalFormat;
    mFormat = format;
    mType = type;
    mWidth = width;
    mHeight = height;
}

void Texture::generateNoise(GLsizei width, GLsizei height)
{
    if (!mId) {
        flThrowException("Texture haven't created yet");
    }
    
    std::vector<Vec4f> data(width * height);
    for (int i=0; i<data.size(); i++) {
        data.at(i).set(randomuf(), randomuf(), randomuf(), randomuf());
    }
    
    bind();
    glTexImage2D(mTarget,
                 0,
                 GL_RGBA,
                 width,
                 height,
                 0,
                 GL_RGBA,
                 GL_FLOAT,
                 &data.at(0).x);
    
    unbind();
    
    mWidth = width;
    mHeight = height;
}

#pragma mark ___________________________________________________________________
void Texture::update(GLint x,
                     GLint y,
                     GLsizei w,
                     GLsizei h,
                     const GLvoid *pixels)
{
    bind();
    glTexSubImage2D(mTarget,
                    0,
                    x,
                    y,
                    w,
                    h,
                    mFormat,
                    mType,
                    pixels);
    unbind();
}

void Texture::setFilter(GLenum min, GLenum mag)
{
    bind();
    glTexParameterf(mTarget, GL_TEXTURE_MAG_FILTER, mag);
    glTexParameterf(mTarget, GL_TEXTURE_MIN_FILTER, min);
    unbind();
}

void Texture::setWrap(GLenum S, GLenum T)
{
    bind();
    glTexParameterf(mTarget, GL_TEXTURE_WRAP_S, S);
    glTexParameterf(mTarget, GL_TEXTURE_WRAP_T, T);
    unbind();
}

#pragma mark ___________________________________________________________________

void Texture::bind() const
{
#ifndef TARGET_OPENGLES
    glEnable(mTarget);
#endif
    glBindTexture(mTarget, mId);
}

void Texture::unbind() const
{
    glBindTexture(mTarget, 0);
#ifndef TARGET_OPENGLES
    glDisable(mTarget);
#endif
}