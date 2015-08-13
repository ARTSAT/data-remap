//
//  flMCTypes.h
//  flTinyGLUtils
//
//  Created by YoshitoONISHI on 8/12/15.
//  Copyright (c) 2015 YoshitoONISHI. All rights reserved.
//

#ifndef flTinyGLUtils_flMCTypes_h
#define flTinyGLUtils_flMCTypes_h

namespace fl {
    namespace MC {
    }
}

#define MULTI_COLOR_NAMESPACE_BEGIN namespace fl { namespace MC {
#define MULTI_COLOR_NAMESPACE_END } }

MULTI_COLOR_NAMESPACE_BEGIN

struct Color {
    double r;
    double g;
    double b;
};

struct Vector {
    double x;
    double y;
    double z;
};

typedef double Matrix[4][4];

extern const Matrix kIdentityMatrix;

void copyMatrix(const Matrix a, Matrix b);
void multMatrix(const Matrix a, const Matrix b, Matrix c);
void rotateX(double theta, Matrix m);
void rotateY(double theta, Matrix m);
void rotateZ(double theta, Matrix m);
Vector vectTransform(const Vector v, const Matrix m);

MULTI_COLOR_NAMESPACE_END

#endif