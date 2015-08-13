//
//  StencilMask.cpp
//  test
//
//  Created by Onishi Yoshito on 6/24/13.
//
//

#include "flStencilMask.h"

using namespace fl;

StencilMask::StencilMask() :
mOp((GLuint)OP_POSITIVE)
{
    
}

StencilMask::~StencilMask()
{
}

void StencilMask::clear()
{
    glClear(GL_STENCIL_BUFFER_BIT);
}

void StencilMask::begin()
{
    glEnable(GL_STENCIL_TEST);
    glStencilFunc( GL_ALWAYS, 1, ~0);
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
    glColorMask(0,0,0,0);
    glDepthMask(0);
}

void StencilMask::end()
{
    glColorMask(1,1,1,1);
    glDepthMask(1);
    glDisable(GL_STENCIL_TEST);
}

void StencilMask::bind()
{
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP,GL_KEEP ,GL_KEEP);
    glStencilFunc(GL_EQUAL, mOp, ~0);
}

void StencilMask::unbind()
{
    glDisable(GL_STENCIL_TEST);
}

void StencilMask::setOp(Op op)
{
    mOp = (GLuint)op;
}