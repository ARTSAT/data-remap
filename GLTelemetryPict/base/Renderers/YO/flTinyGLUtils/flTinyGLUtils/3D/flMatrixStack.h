//
//  flMatrixStack.h
//  flTinyGLUtils
//
//  Created by Onishi Yoshito on 10/29/13.
//  Copyright (c) 2013 Onishi Yoshito. All rights reserved.
//

#ifndef __DrawXmasTest__flMatrixStack__
#define __DrawXmasTest__flMatrixStack__

#include <stack>
#include <float.h>
#include <vector>
#include "flCommon.h"

FL_NAMESPACE_BEGIN

class Matrix4x4;
class Vec3f;
class Quaternion;

enum Matrix {
    MATRIX_MODELVIEW,
    MATRIX_PROJECTION,
    NUM_MATRICES,
};

class MatrixStack {
public:
    MatrixStack();
    
    void setMode(int _mode);
    
    void pushMatrix();
    void popMatrix();
    
    void loadIdentity();
    void loadMatrix(const Matrix4x4& m);
    void multMatrix(const Matrix4x4& m);
    
    void translate(float x, float y, float z = 0.f);
    void translate(const Vec3f& pos);
    
    void scale(float x, float y, float z);
    void scale(const Vec3f& scale);
    
    void rotate(float degrees, float x, float y, float z);
    void rotate(const Quaternion& quat);
    
    Matrix4x4& currentMatrix();
    
    std::stack<Matrix4x4>& currentStack();
    
    Matrix4x4& getMatrix(int mode);
    
    void addStack();
    
    Matrix4x4 getModelViewProjectionMatrix();
    
private:
    std::vector<std::stack<Matrix4x4> > stacks;
    std::vector<Matrix4x4> matrices;
    int mode;
    
};

FL_NAMESPACE_END

#endif /* defined(__flTinyGLUtils__flMatrixStack__) */
