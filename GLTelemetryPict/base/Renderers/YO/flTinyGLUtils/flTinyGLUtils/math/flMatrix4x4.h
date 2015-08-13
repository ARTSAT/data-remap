/* port from oF */

/*
 *  Matrix4x4.h
 *
 *  Created by Aaron Meyers on 6/22/09 -- modified by Arturo Castro, Zach Lieberman, Memo Akten
 *  based on code from OSG -
 *  see OSG license for more details:
 *  http://www.openscenegraph.org/projects/osg/wiki/Legal
 *
 */

#pragma once

#include <cmath>
#include <iomanip>

#include "flVec4f.h"
#include "flQuaternion.h"
#include "flMath.h"
#include "flCommon.h"

FL_NAMESPACE_BEGIN

class Matrix4x4 {
public:
    //	float _mat[4][4];
    Vec4f _mat[4];
    
    //---------------------------------------------
    // constructors
    Matrix4x4() {
        makeIdentityMatrix();
    }
    Matrix4x4( const Matrix4x4& mat) {
        set(mat.getPtr());
    }
    Matrix4x4( float const * const ptr ) {
        set(ptr);
    }
    Matrix4x4( const Quaternion& quat ) {
        makeRotationMatrix(quat);
    }
    
    Matrix4x4(	float a00, float a01, float a02, float a03,
              float a10, float a11, float a12, float a13,
              float a20, float a21, float a22, float a23,
              float a30, float a31, float a32, float a33);
    
    //---------------------------------------------
    // destructor
    ~Matrix4x4() {}
    
    //	int compare(const Matrix4x4& m) const;
    //
    //	bool operator < (const Matrix4x4& m) const { return compare(m)<0; }
    //	bool operator == (const Matrix4x4& m) const { return compare(m)==0; }
    //	bool operator != (const Matrix4x4& m) const { return compare(m)!=0; }
    
    //---------------------------------------------
    // write data with matrix(row,col)=number
    float& operator()(int row, int col) {
        return _mat[row][col];
    }
    
    //---------------------------------------------
    // read data with var=matrix(row,col)
    float operator()(int row, int col) const {
        return _mat[row][col];
    }
    
    //----------------------------------------
    Vec4f getRowAsVec3f(int i) const {
        return Vec4f(_mat[i][0], _mat[i][1], _mat[i][2]);
    }
    
    //----------------------------------------
    Vec4f getRowAsVec4f(int i) const {
        return _mat[i];
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Matrix4x4& M);
    friend std::istream& operator>>(std::istream& is, Matrix4x4& M);
    
    //---------------------------------------------
    // check if the matrix is valid
    bool isValid() const {
        return !isNaN();
    }
    
    bool isNaN() const;
    
    //---------------------------------------------
    // copy a matrix using = operator
    Matrix4x4& operator = (const Matrix4x4& rhs);
    
    //---------------------------------------------
    // methods to set the data of the matrix
    void set(const Matrix4x4& rhs);
    void set(float const * const ptr);
    void set(double const * const ptr);
    void set(float a00, float a01, float a02, float a03,
             float a10, float a11, float a12, float a13,
             float a20, float a21, float a22, float a23,
             float a30, float a31, float a32, float a33);
    
    //---------------------------------------------
    // access the internal data in float* format
    // useful for opengl matrix transformations
    float * getPtr() {
        return (float*)_mat;
    }
    const float * getPtr() const {
        return (const float *)_mat;
    }
    
    //---------------------------------------------
    // check matrix identity
    bool isIdentity() const;
    
    
    //---------------------------------------------
    // init matrix as identity, scale, translation...
    // all make* methods delete the current data
    void makeIdentityMatrix();
    
    void makeScaleMatrix( const Vec4f& );
    void makeScaleMatrix( float, float, float );
    
    void makeTranslationMatrix( const Vec4f& );
    void makeTranslationMatrix( float, float, float );
    
    void makeRotationMatrix( const Vec4f& from, const Vec4f& to );
    void makeRotationMatrix( float angle, const Vec4f& axis );
    void makeRotationMatrix( float angle, float x, float y, float z );
    void makeRotationMatrix( const Quaternion& );
    void makeRotationMatrix( float angle1, const Vec4f& axis1,
                            float angle2, const Vec4f& axis2,
                            float angle3, const Vec4f& axis3);
    
    
    // init related to another matrix
    bool makeInvertOf( const Matrix4x4& rhs);
    void makeOrthoNormalOf(const Matrix4x4& rhs);
    void makeFromMultiplicationOf( const Matrix4x4&, const Matrix4x4& );
    
    Matrix4x4 getInverse();
    
    
    //---------------------------------------------
    // init as opengl related matrix for perspective settings
    // see opengl docs of the related funciton for further details
    
    // glOrtho
    void makeOrthoMatrix(double left,   double right,
                         double bottom, double top,
                         double zNear,  double zFar);
    
    // glOrtho2D
    void makeOrtho2DMatrix(double left,   double right,
                           double bottom, double top);
    
    // glFrustum
    void makeFrustumMatrix(double left,   double right,
                           double bottom, double top,
                           double zNear,  double zFar);
    
    // gluPerspective
    // Aspect ratio is defined as width/height.
    void makePerspectiveMatrix(double fovy,  double aspectRatio,
                               double zNear, double zFar);
    
    
    // makeLookAtMatrix:
    // creates a transformation matrix positioned at 'eye'
    // pointing at (along z axis) 'center'
    // this is what you use if you want an object to look at a point
    void makeLookAtMatrix(const Vec4f& eye, const Vec4f& center, const Vec4f& up);
    
    
    // makeLookAtViewMatrix:
    // creates *the inverse of* a transformation matrix positioned at 'eye'
    // pointing at (along z axis) 'center'
    // this is what you use when you want your view matrix looking at a point
    // (the inverse of makeLookAtMatrix), same as gluLookAt
    void makeLookAtViewMatrix(const Vec4f& eye, const Vec4f& center, const Vec4f& up);
    
    
    //---------------------------------------------
    // Get the perspective components from a matrix
    // this only works with pure perspective projection matrices
    
    bool getOrtho(double& left,   double& right,
                  double& bottom, double& top,
                  double& zNear,  double& zFar) const;
    
    bool getFrustum(double& left,   double& right,
                    double& bottom, double& top,
                    double& zNear,  double& zFar) const;
    
    /** Get the frustum settings of a symmetric perspective projection
     * matrix.
     * Return false if matrix is not a perspective matrix,
     * where parameter values are undefined.
     * Note, if matrix is not a symmetric perspective matrix then the
     * shear will be lost.
     * Asymmetric matrices occur when stereo, power walls, caves and
     * reality center display are used.
     * In these configuration one should use the AsFrustum method instead.
     */
    bool getPerspective(double& fovy,  double& aspectRatio,
                        double& zNear, double& zFar) const;
    
    // will only work for modelview matrices
    void getLookAt(Vec4f& eye, Vec4f& center, Vec4f& up,
                   float lookDistance = 1.0f) const;
    
    
    
    //---------------------------------------------
    // decompose the matrix into translation, rotation,
    // scale and scale orientation.
    void decompose( Vec4f& translation,
                   Quaternion& rotation,
                   Vec4f& scale,
                   Quaternion& so ) const;
    
    
    //---------------------------------------------
    // basic utility functions to create new matrices
    inline static Matrix4x4 newIdentityMatrix( void );
    inline static Matrix4x4 newScaleMatrix( const Vec4f& sv);
    inline static Matrix4x4 newScaleMatrix( float sx, float sy, float sz);
    inline static Matrix4x4 newTranslationMatrix( const Vec4f& dv);
    inline static Matrix4x4 newTranslationMatrix( float x, float y, float z);
    inline static Matrix4x4 newRotationMatrix( const Vec4f& from, const Vec4f& to);
    inline static Matrix4x4 newRotationMatrix( float angle, float x, float y, float z);
    inline static Matrix4x4 newRotationMatrix( float angle, const Vec4f& axis);
    inline static Matrix4x4 newRotationMatrix( float angle1, const Vec4f& axis1,
                                              float angle2, const Vec4f& axis2,
                                              float angle3, const Vec4f& axis3);
    inline static Matrix4x4 newRotationMatrix( const Quaternion& quat);
    
    
    // create new matrices as transformation of another
    inline static Matrix4x4 getInverseOf( const Matrix4x4& matrix);
    inline static Matrix4x4 getTransposedOf( const Matrix4x4& matrix);
    inline static Matrix4x4 getOrthoNormalOf(const Matrix4x4& matrix);
    
    
    // create new matrices related to glFunctions
    
    // glOrtho
    inline static Matrix4x4 newOrthoMatrix(double left,   double right,
                                           double bottom, double top,
                                           double zNear,  double zFar);
    
    // glOrtho2D
    inline static Matrix4x4 newOrtho2DMatrix(double left,   double right,
                                             double bottom, double top);
    
    // glFrustum
    inline static Matrix4x4 newFrustumMatrix(double left,   double right,
                                             double bottom, double top,
                                             double zNear,  double zFar);
    
    // gluPerspective
    inline static Matrix4x4 newPerspectiveMatrix(double fovy,  double aspectRatio,
                                                 double zNear, double zFar);
    
    // gluLookAt
    inline static Matrix4x4 newLookAtMatrix(const Vec4f& eye,
                                            const Vec4f& center,
                                            const Vec4f& up);
    
    
    //---------------------------------------------
    // matrix - vector multiplication
    // although opengl uses premultiplication
    // because of the way matrices are used in opengl:
    //
    // Matrix4x4				openGL
    // [0]  [1]  [2]  [3]		[0] [4] [8]  [12]
    // [4]  [5]  [6]  [7]		[1] [5] [9]  [13]
    // [8]  [9]  [10] [11]		[2] [6] [10] [14]
    // [12] [13] [14] [15]		[3] [7] [11] [15]
    //
    // in memory though both are layed in the same way
    // so when uploading a matrix it just works without
    // needing to transpose
    //
    // so although opengl docs explain transformations
    // like:
    //
    // Vec4f c = rotateZ 30º Vec4f a around Vec4f b
    //
    // openGL docs says: c = T(b)*R(30)*a;
    //
    // with Matrix4x4:
    // Matrix4x4 R = Matrix4x4::newRotationMatrix(30,0,0,1);
    // Matrix4x4 T = Matrix4x4::newTranlationMatrix(b);
    // Vec4f c = a*R*T;
    // where * is calling postMult
    
    inline Vec4f postMult( const Vec4f& v ) const;
    inline Vec4f operator* (const Vec4f& v) const {
        return postMult(v);
    }
    
    inline Vec4f preMult( const Vec4f& v ) const;
    
    //---------------------------------------------
    // set methods: all these alter the components
    // deleting the previous data only in that components
    void setRotate(const Quaternion& q);
    void setTranslation( float tx, float ty, float tz );
    void setTranslation( const Vec4f& v );
    
    //---------------------------------------------
    // all these apply the transformations over the
    // current one, it's actually postMult... and behaves
    // the opposite to the equivalent gl functions
    // glTranslate + glRotate == rotate + translate
    void rotate(float angle, float x, float y, float z);
    void rotateRad(float angle, float x, float y, float z);
    void rotate(const Quaternion& q);
    void translate( float tx, float ty, float tz );
    void translate( const Vec4f& v );
    void scale(float x, float y, float z);
    void scale( const Vec4f& v );
    
    //---------------------------------------------
    // all these apply the transformations over the
    // current one, it's actually preMult... and behaves
    // the the same the equivalent gl functions
    void glRotate(float angle, float x, float y, float z);
    void glRotateRad(float angle, float x, float y, float z);
    void glRotate(const Quaternion& q);
    void glTranslate( float tx, float ty, float tz );
    void glTranslate( const Vec4f& v );
    void glScale(float x, float y, float z);
    void glScale( const Vec4f& v );
    
    //---------------------------------------------
    // get methods: return matrix components
    // rotation and scale can only be used if the matrix
    // only has rotation or scale.
    // for matrices with both use decompose instead.
    Quaternion getRotate() const;
    Vec4f getTranslation() const;
    Vec4f getScale() const;
    
    
    //---------------------------------------------
    // apply a 3x3 transform of v*M[0..2,0..2].
    inline static Vec4f transform3x3(const Vec4f& v, const Matrix4x4& m);
    
    // apply a 3x3 transform of M[0..2,0..2]*v.
    inline static Vec4f transform3x3(const Matrix4x4& m, const Vec4f& v);
    
    
    //---------------------------------------------
    // basic Matrixf multiplication, our workhorse methods.
    void postMult( const Matrix4x4& );
    inline void operator *= ( const Matrix4x4& other ) {
        if ( this == &other ) {
            Matrix4x4 temp(other);
            postMult( temp );
        } else postMult( other );
    }
    
    inline Matrix4x4 operator * ( const Matrix4x4 &m ) const {
        Matrix4x4 r;
        r.makeFromMultiplicationOf(*this, m);
        return  r;
    }
    
    
    
    void preMult( const Matrix4x4& );
    
    
    
    //---------------------------------------------
    // specialized postMult methods, usually you want to use this
    // for transforming ofVec not preMult
    // equivalent to postMult(newTranslationMatrix(v)); */
    inline void postMultTranslate( const Vec4f& v );
    // equivalent to postMult(scale(v));
    inline void postMultScale( const Vec4f& v );
    // equivalent to postMult(newRotationMatrix(q));
    inline void postMultRotate( const Quaternion& q );
    
    // AARON METHODS
    inline void postMultTranslate(float x, float y, float z);
    inline void postMultRotate(float angle, float x, float y, float z);
    inline void postMultScale(float x, float y, float z);
    
    
    //---------------------------------------------
    // equivalent to preMult(newScaleMatrix(v));
    inline void preMultScale( const Vec4f& v );
    // equivalent to preMult(newTranslationMatrix(v));
    inline void preMultTranslate( const Vec4f& v );
    // equivalent to preMult(newRotationMatrix(q));
    inline void preMultRotate( const Quaternion& q );
};


//--------------------------------------------------
// implementation of inline methods

inline bool Matrix4x4::isNaN() const {
    
#if (_MSC_VER) || defined (TARGET_ANDROID)
#ifndef isnan
#define isnan(a) ((a) != (a))
#endif
    
    return isnan(_mat[0][0]) || isnan(_mat[0][1]) || isnan(_mat[0][2]) || isnan(_mat[0][3]) ||
    isnan(_mat[1][0]) || isnan(_mat[1][1]) || isnan(_mat[1][2]) || isnan(_mat[1][3]) ||
    isnan(_mat[2][0]) || isnan(_mat[2][1]) || isnan(_mat[2][2]) || isnan(_mat[2][3]) ||
    isnan(_mat[3][0]) || isnan(_mat[3][1]) || isnan(_mat[3][2]) || isnan(_mat[3][3]);
    
#else
    return std::isnan(_mat[0][0]) || std::isnan(_mat[0][1]) || std::isnan(_mat[0][2]) || std::isnan(_mat[0][3]) ||
    std::isnan(_mat[1][0]) || std::isnan(_mat[1][1]) || std::isnan(_mat[1][2]) || std::isnan(_mat[1][3]) ||
    std::isnan(_mat[2][0]) || std::isnan(_mat[2][1]) || std::isnan(_mat[2][2]) || std::isnan(_mat[2][3]) ||
    std::isnan(_mat[3][0]) || std::isnan(_mat[3][1]) || std::isnan(_mat[3][2]) || std::isnan(_mat[3][3]);
    
#endif
    
}



inline std::ostream& operator<<(std::ostream& os, const Matrix4x4& M) {
    int w = 8;
    os	<< std::setw(w)
    << M._mat[0][0] << ", " << std::setw(w)
    << M._mat[0][1] << ", " << std::setw(w)
    << M._mat[0][2] << ", " << std::setw(w)
    << M._mat[0][3] << std::endl;
    
    os	<< std::setw(w)
    << M._mat[1][0] << ", " << std::setw(w)
    << M._mat[1][1] << ", " << std::setw(w)
    << M._mat[1][2] << ", " << std::setw(w)
    << M._mat[1][3] << std::endl;
    
    os	<< std::setw(w)
    << M._mat[2][0] << ", " << std::setw(w)
    << M._mat[2][1] << ", " << std::setw(w)
    << M._mat[2][2] << ", " << std::setw(w)
    << M._mat[2][3] << std::endl;
    
    os	<< std::setw(w)
    << M._mat[3][0] << ", " << std::setw(w)
    << M._mat[3][1] << ", " << std::setw(w)
    << M._mat[3][2] << ", " << std::setw(w)
    << M._mat[3][3];
    
    return os;
}

inline std::istream& operator>>(std::istream& is, Matrix4x4& M) {
    is >> M._mat[0][0]; is.ignore(2);
    is >> M._mat[0][1]; is.ignore(2);
    is >> M._mat[0][2]; is.ignore(2);
    is >> M._mat[0][3]; is.ignore(1);
    
    is >> M._mat[1][0]; is.ignore(2);
    is >> M._mat[1][1]; is.ignore(2);
    is >> M._mat[1][2]; is.ignore(2);
    is >> M._mat[1][3]; is.ignore(1);
    
    is >> M._mat[2][0]; is.ignore(2);
    is >> M._mat[2][1]; is.ignore(2);
    is >> M._mat[2][2]; is.ignore(2);
    is >> M._mat[2][3]; is.ignore(1);
    
    is >> M._mat[3][0]; is.ignore(2);
    is >> M._mat[3][1]; is.ignore(2);
    is >> M._mat[3][2]; is.ignore(2);
    is >> M._mat[3][3];
    return is;
}


inline Matrix4x4& Matrix4x4::operator = (const Matrix4x4& rhs) {
    if ( &rhs == this ) return *this;
    set(rhs.getPtr());
    return *this;
}

inline void Matrix4x4::set(const Matrix4x4& rhs) {
    set(rhs.getPtr());
}

inline void Matrix4x4::set(float const * const ptr) {
    float* local_ptr = (float*)_mat;
    for (int i = 0;i < 16;++i) local_ptr[i] = (float)ptr[i];
}

inline void Matrix4x4::set(double const * const ptr) {
    float* local_ptr = (float*)_mat;
    for (int i = 0;i < 16;++i) local_ptr[i] = (float)ptr[i];
}

inline bool Matrix4x4::isIdentity() const {
    return _mat[0][0] == 1.0f && _mat[0][1] == 0.0f && _mat[0][2] == 0.0f &&  _mat[0][3] == 0.0f &&
    _mat[1][0] == 0.0f && _mat[1][1] == 1.0f && _mat[1][2] == 0.0f &&  _mat[1][3] == 0.0f &&
    _mat[2][0] == 0.0f && _mat[2][1] == 0.0f && _mat[2][2] == 1.0f &&  _mat[2][3] == 0.0f &&
    _mat[3][0] == 0.0f && _mat[3][1] == 0.0f && _mat[3][2] == 0.0f &&  _mat[3][3] == 1.0f;
}

inline void Matrix4x4::makeOrtho2DMatrix(double left,   double right,
                                         double bottom, double top) {
    makeOrthoMatrix(left, right, bottom, top, -1.0, 1.0);
}

inline Vec4f Matrix4x4::getTranslation() const {
    return Vec4f(_mat[3][0], _mat[3][1], _mat[3][2]);
}

inline Vec4f Matrix4x4::getScale() const {
    Vec4f x_vec(_mat[0][0], _mat[1][0], _mat[2][0]);
    Vec4f y_vec(_mat[0][1], _mat[1][1], _mat[2][1]);
    Vec4f z_vec(_mat[0][2], _mat[1][2], _mat[2][2]);
    return Vec4f(x_vec.length(), y_vec.length(), z_vec.length());
}

//static utility methods
inline Matrix4x4 Matrix4x4::newIdentityMatrix(void) {
    Matrix4x4 m;
    m.makeIdentityMatrix();
    return m;
}

inline Matrix4x4 Matrix4x4::newScaleMatrix(float sx, float sy, float sz) {
    Matrix4x4 m;
    m.makeScaleMatrix(sx, sy, sz);
    return m;
}

inline Matrix4x4 Matrix4x4::newScaleMatrix(const Vec4f& v ) {
    return newScaleMatrix(v.x, v.y, v.z );
}

inline Matrix4x4 Matrix4x4::newTranslationMatrix(float tx, float ty, float tz) {
    Matrix4x4 m;
    m.makeTranslationMatrix(tx, ty, tz);
    return m;
}

inline Matrix4x4 Matrix4x4::newTranslationMatrix(const Vec4f& v ) {
    return newTranslationMatrix(v.x, v.y, v.z );
}

inline Matrix4x4 Matrix4x4::newRotationMatrix( const Quaternion& q ) {
    return Matrix4x4(q);
}
inline Matrix4x4 Matrix4x4::newRotationMatrix(float angle, float x, float y, float z ) {
    Matrix4x4 m;
    m.makeRotationMatrix(angle, x, y, z);
    return m;
}
inline Matrix4x4 Matrix4x4::newRotationMatrix(float angle, const Vec4f& axis ) {
    Matrix4x4 m;
    m.makeRotationMatrix(angle, axis);
    return m;
}
inline Matrix4x4 Matrix4x4::newRotationMatrix(	float angle1, const Vec4f& axis1,
                                              float angle2, const Vec4f& axis2,
                                              float angle3, const Vec4f& axis3) {
    Matrix4x4 m;
    m.makeRotationMatrix(angle1, axis1, angle2, axis2, angle3, axis3);
    return m;
}
inline Matrix4x4 Matrix4x4::newRotationMatrix(const Vec4f& from, const Vec4f& to ) {
    Matrix4x4 m;
    m.makeRotationMatrix(from, to);
    return m;
}

inline Matrix4x4 Matrix4x4::getInverseOf( const Matrix4x4& matrix) {
    Matrix4x4 m;
    m.makeInvertOf(matrix);
    return m;
}

inline Matrix4x4 Matrix4x4::getTransposedOf( const Matrix4x4& matrix) {
    Matrix4x4 m(matrix._mat[0][0], matrix._mat[1][0], matrix._mat[2][0],
                matrix._mat[3][0], matrix._mat[0][1], matrix._mat[1][1], matrix._mat[2][1],
                matrix._mat[3][1], matrix._mat[0][2], matrix._mat[1][2], matrix._mat[2][2],
                matrix._mat[3][2], matrix._mat[0][3], matrix._mat[1][3], matrix._mat[2][3],
                matrix._mat[3][3]);
    return m;
}

inline Matrix4x4 Matrix4x4::getOrthoNormalOf(const Matrix4x4& matrix) {
    Matrix4x4 m;
    m.makeOrthoNormalOf(matrix);
    return m;
}

inline Matrix4x4 Matrix4x4::newOrthoMatrix(double left, double right,
                                           double bottom, double top,
                                           double zNear, double zFar) {
    Matrix4x4 m;
    m.makeOrthoMatrix(left, right, bottom, top, zNear, zFar);
    return m;
}

inline Matrix4x4 Matrix4x4::newOrtho2DMatrix(double left, double right,
                                             double bottom, double top) {
    Matrix4x4 m;
    m.makeOrtho2DMatrix(left, right, bottom, top);
    return m;
}

inline Matrix4x4 Matrix4x4::newFrustumMatrix(double left, double right,
                                             double bottom, double top,
                                             double zNear, double zFar) {
    Matrix4x4 m;
    m.makeFrustumMatrix(left, right, bottom, top, zNear, zFar);
    return m;
}

inline Matrix4x4 Matrix4x4::newPerspectiveMatrix(double fovy, double aspectRatio,
                                                 double zNear, double zFar) {
    Matrix4x4 m;
    m.makePerspectiveMatrix(fovy, aspectRatio, zNear, zFar);
    return m;
}

inline Matrix4x4 Matrix4x4::newLookAtMatrix(const Vec4f& eye, const Vec4f& center, const Vec4f& up) {
    Matrix4x4 m;
    m.makeLookAtMatrix(eye, center, up);
    return m;
}

inline Vec4f Matrix4x4::postMult( const Vec4f& v ) const {
    float d = 1.0f / (_mat[3][0] * v.x + _mat[3][1] * v.y + _mat[3][2] * v.z + _mat[3][3]) ;
    return Vec4f( (_mat[0][0]*v.x + _mat[0][1]*v.y + _mat[0][2]*v.z + _mat[0][3])*d,
                 (_mat[1][0]*v.x + _mat[1][1]*v.y + _mat[1][2]*v.z + _mat[1][3])*d,
                 (_mat[2][0]*v.x + _mat[2][1]*v.y + _mat[2][2]*v.z + _mat[2][3])*d) ;
}

inline Vec4f Matrix4x4::preMult( const Vec4f& v ) const {
    float d = 1.0f / (_mat[0][3] * v.x + _mat[1][3] * v.y + _mat[2][3] * v.z + _mat[3][3]) ;
    return Vec4f( (_mat[0][0]*v.x + _mat[1][0]*v.y + _mat[2][0]*v.z + _mat[3][0])*d,
                 (_mat[0][1]*v.x + _mat[1][1]*v.y + _mat[2][1]*v.z + _mat[3][1])*d,
                 (_mat[0][2]*v.x + _mat[1][2]*v.y + _mat[2][2]*v.z + _mat[3][2])*d);
}

inline Vec4f Matrix4x4::transform3x3(const Vec4f& v, const Matrix4x4& m) {
    return Vec4f( (m._mat[0][0]*v.x + m._mat[1][0]*v.y + m._mat[2][0]*v.z),
                 (m._mat[0][1]*v.x + m._mat[1][1]*v.y + m._mat[2][1]*v.z),
                 (m._mat[0][2]*v.x + m._mat[1][2]*v.y + m._mat[2][2]*v.z));
}

inline Vec4f Matrix4x4::transform3x3(const Matrix4x4& m, const Vec4f& v) {
    return Vec4f( (m._mat[0][0]*v.x + m._mat[0][1]*v.y + m._mat[0][2]*v.z),
                 (m._mat[1][0]*v.x + m._mat[1][1]*v.y + m._mat[1][2]*v.z),
                 (m._mat[2][0]*v.x + m._mat[2][1]*v.y + m._mat[2][2]*v.z) ) ;
}

inline void Matrix4x4::preMultTranslate( const Vec4f& v ) {
    for (unsigned i = 0; i < 3; ++i) {
        float tmp = v.getPtr()[i];
        if (tmp == 0)
            continue;
        _mat[3][0] += tmp * _mat[i][0];
        _mat[3][1] += tmp * _mat[i][1];
        _mat[3][2] += tmp * _mat[i][2];
        _mat[3][3] += tmp * _mat[i][3];
    }
}

inline void Matrix4x4::postMultTranslate( const Vec4f& v ) {
    for (unsigned i = 0; i < 3; ++i) {
        float tmp = v.getPtr()[i];
        if (tmp == 0)
            continue;
        _mat[0][i] += tmp * _mat[0][3];
        _mat[1][i] += tmp * _mat[1][3];
        _mat[2][i] += tmp * _mat[2][3];
        _mat[3][i] += tmp * _mat[3][3];
    }
}

// AARON METHOD
inline void Matrix4x4::postMultTranslate( float x, float y, float z) {
    if (x != 0) {
        _mat[0][0] += x * _mat[0][3];
        _mat[1][0] += x * _mat[1][3];
        _mat[2][0] += x * _mat[2][3];
        _mat[3][0] += x * _mat[3][3];
    }
    if (y != 0) {
        _mat[0][1] += y * _mat[0][3];
        _mat[1][1] += y * _mat[1][3];
        _mat[2][1] += y * _mat[2][3];
        _mat[3][1] += y * _mat[3][3];
    }
    if (z != 0) {
        _mat[0][2] += z * _mat[0][3];
        _mat[1][2] += z * _mat[1][3];
        _mat[2][2] += z * _mat[2][3];
        _mat[3][2] += z * _mat[3][3];
    }
}

inline void Matrix4x4::preMultScale( const Vec4f& v ) {
    _mat[0][0] *= v.getPtr()[0];
    _mat[0][1] *= v.getPtr()[0];
    _mat[0][2] *= v.getPtr()[0];
    _mat[0][3] *= v.getPtr()[0];
    _mat[1][0] *= v.getPtr()[1];
    _mat[1][1] *= v.getPtr()[1];
    _mat[1][2] *= v.getPtr()[1];
    _mat[1][3] *= v.getPtr()[1];
    _mat[2][0] *= v.getPtr()[2];
    _mat[2][1] *= v.getPtr()[2];
    _mat[2][2] *= v.getPtr()[2];
    _mat[2][3] *= v.getPtr()[2];
}

inline void Matrix4x4::postMultScale( const Vec4f& v ) {
    _mat[0][0] *= v.getPtr()[0];
    _mat[1][0] *= v.getPtr()[0];
    _mat[2][0] *= v.getPtr()[0];
    _mat[3][0] *= v.getPtr()[0];
    _mat[0][1] *= v.getPtr()[1];
    _mat[1][1] *= v.getPtr()[1];
    _mat[2][1] *= v.getPtr()[1];
    _mat[3][1] *= v.getPtr()[1];
    _mat[0][2] *= v.getPtr()[2];
    _mat[1][2] *= v.getPtr()[2];
    _mat[2][2] *= v.getPtr()[2];
    _mat[3][2] *= v.getPtr()[2];
}

inline void Matrix4x4::rotate(const Quaternion& q){
    postMultRotate(q);
}

inline void Matrix4x4::rotate(float angle, float x, float y, float z){
    postMultRotate(angle,x,y,z);
}

inline void Matrix4x4::rotateRad(float angle, float x, float y, float z){
    postMultRotate(angle*RAD_TO_DEG,x,y,z);
}

inline void Matrix4x4::translate( float tx, float ty, float tz ){
    postMultTranslate(tx,ty,tz);
}

inline void Matrix4x4::translate( const Vec4f& v ){
    postMultTranslate(v);
}

inline void Matrix4x4::scale(float x, float y, float z){
    postMultScale(x,y,z);
}

inline void Matrix4x4::scale( const Vec4f& v ){
    postMultScale(v);
}

inline void Matrix4x4::glRotate(float angle, float x, float y, float z){
    preMultRotate(Quaternion(angle,Vec4f(x,y,z)));
}

inline void Matrix4x4::glRotateRad(float angle, float x, float y, float z){
    preMultRotate(Quaternion(angle*RAD_TO_DEG,Vec4f(x,y,z)));
}

inline void Matrix4x4::glRotate(const Quaternion& q){
    preMultRotate(q);
}

inline void Matrix4x4::glTranslate( float tx, float ty, float tz ){
    preMultTranslate(Vec4f(tx,ty,tz));
}

inline void Matrix4x4::glTranslate( const Vec4f& v ){
    preMultTranslate(v);
}

inline void Matrix4x4::glScale(float x, float y, float z){
    preMultScale(Vec4f(x,y,z));
}

inline void Matrix4x4::glScale( const Vec4f& v ){
    preMultScale(v);
}

// AARON METHOD
inline void Matrix4x4::postMultScale( float x, float y, float z ) {
    _mat[0][0] *= x;
    _mat[1][0] *= x;
    _mat[2][0] *= x;
    _mat[3][0] *= x;
    _mat[0][1] *= y;
    _mat[1][1] *= y;
    _mat[2][1] *= y;
    _mat[3][1] *= y;
    _mat[0][2] *= z;
    _mat[1][2] *= z;
    _mat[2][2] *= z;
    _mat[3][2] *= z;
}


inline void Matrix4x4::preMultRotate( const Quaternion& q ) {
    if (q.zeroRotation())
        return;
    Matrix4x4 r;
    r.setRotate(q);
    preMult(r);
}

inline void Matrix4x4::postMultRotate( const Quaternion& q ) {
    if (q.zeroRotation())
        return;
    Matrix4x4 r;
    r.setRotate(q);
    postMult(r);
}

// AARON METHOD
inline void Matrix4x4::postMultRotate(float angle, float x, float y, float z) {
    Matrix4x4 r;
    r.makeRotationMatrix(angle, x, y, z);
    postMult(r);
}



inline Vec4f operator* (const Vec4f& v, const Matrix4x4& m ) {
    return m.preMult(v);
}

FL_NAMESPACE_END
