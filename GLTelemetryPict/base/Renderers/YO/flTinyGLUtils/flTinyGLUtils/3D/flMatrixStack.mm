//
//  flMatrixStack.cpp
//  flTinyGLUtils
//
//  Created by Onishi Yoshito on 10/29/13.
//  Copyright (c) 2013 Onishi Yoshito. All rights reserved.
//

#include "flMatrixStack.h"

#include "flCommon.h"
#include "flMatrix4x4.h"
#include "flVec3f.h"
#include "flVec4f.h"
#include "flQuaternion.h"
#include "flException.h"
#include "flUtils.h"

FL_NAMESPACE_BEGIN

MatrixStack::MatrixStack() :
mode(0),
matrices(NUM_MATRICES),
stacks(NUM_MATRICES)
{
    for (auto& m : matrices) {
        m.makeIdentityMatrix();
    }
}

void MatrixStack::setMode(int _mode)
{
    if (_mode<0 || _mode>=matrices.size()) {
        flThrowException("MatrixStack out of range");
    }
    mode = _mode;
}

void MatrixStack::pushMatrix()
{
    stacks.at(mode).push(matrices.at(mode));
}

void MatrixStack::popMatrix()
{
    matrices.at(mode) = stacks.at(mode).top();
    stacks.at(mode).pop();
}

void MatrixStack::loadIdentity()
{
    currentMatrix().makeIdentityMatrix();
}

void MatrixStack::loadMatrix(const Matrix4x4& m)
{
    currentMatrix().set(m);
}

void MatrixStack::multMatrix(const Matrix4x4& m)
{
    currentMatrix().preMult(m);
}

void MatrixStack::translate(float x, float y, float z)
{
    currentMatrix().glTranslate(x, y, z);
}

void MatrixStack::translate(const Vec3f& pos)
{
    currentMatrix().glTranslate(Vec4f(pos.x, pos.y, pos.z, 1.f));
}

void MatrixStack::scale(float x, float y, float z)
{
    currentMatrix().glScale(x, y, z);
}

void MatrixStack::scale(const Vec3f& scale)
{
    currentMatrix().glScale(Vec4f(scale.x, scale.y, scale.z, 1.f));
}

void MatrixStack::rotate(float degrees, float x, float y, float z)
{
    currentMatrix().glRotate(degrees, x, y, z);
}

void MatrixStack::rotate(const Quaternion& quat)
{
    Vec4f axis;
    float angle;
    quat.getRotate(angle, axis);
    if(fabsf(angle) > FLT_EPSILON) {
        rotate(angle, axis.x, axis.y, axis.z);
    }
}

Matrix4x4& MatrixStack::currentMatrix()
{
    return matrices.at(mode);
}

std::stack<Matrix4x4>& MatrixStack::currentStack()
{
    return stacks.at(mode);
}

Matrix4x4& MatrixStack::getMatrix(int mode)
{
    if (mode<0 || mode>=matrices.size()) {
        flThrowException("MatrixStack out of range");
    }
    return matrices.at(mode);
}

void MatrixStack::addStack()
{
    stacks.push_back(std::stack<Matrix4x4>());
    matrices.push_back(Matrix4x4());
    (matrices.end()-1)->makeIdentityMatrix();
}

Matrix4x4 MatrixStack::getModelViewProjectionMatrix()
{
    return getMatrix(MATRIX_MODELVIEW) * getMatrix(MATRIX_PROJECTION);
}

FL_NAMESPACE_END